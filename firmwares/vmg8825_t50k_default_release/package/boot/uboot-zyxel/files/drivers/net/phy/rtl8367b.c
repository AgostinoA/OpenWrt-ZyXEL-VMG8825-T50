#include <common.h>
#include <command.h>

#define MDC_MDIO_DUMMY_ID           0
#define MDC_MDIO_CTRL0_REG          31
#define MDC_MDIO_START_REG          29
#define MDC_MDIO_CTRL1_REG          21
#define MDC_MDIO_ADDRESS_REG        23
#define MDC_MDIO_DATA_WRITE_REG     24
#define MDC_MDIO_DATA_READ_REG      25
#define MDC_MDIO_PREAMBLE_LEN       32

#define MDC_MDIO_START_OP          0xFFFF
#define MDC_MDIO_ADDR_OP           0x000E
#define MDC_MDIO_READ_OP           0x0001
#define MDC_MDIO_WRITE_OP          0x0003

#define PHY_INTERNALNOMAX        0x4
#define PHY_REGNOMAX		         0x1F


#ifdef CONFIG_MII
        #include <miiphy.h>

static char *mii_dev_name=NULL;

        #define MDC_MDIO_READ(preamble_len, addr, reg, val)       miiphy_read(mii_dev_name, addr, reg, val)
        #define MDC_MDIO_WRITE(preamble_len, addr, reg, val)      miiphy_write(mii_dev_name, addr, reg, val)
#else
  #ifdef CONFIG_RT2880_ETH
        #define MDC_MDIO_READ(preamble_len, addr, reg, val)       mii_mgr_read(addr, reg, val)
        #define MDC_MDIO_WRITE(preamble_len, addr, reg, val)      mii_mgr_write(addr, reg, val)
  #else
    #error "No mdio driver for RT8367B!"
  #endif
#endif

static int register_read(u32 mAddrs, u32 *rData)
{
#ifdef CONFIG_MII
        char *old_name = miiphy_get_current_dev();
        if ( miiphy_set_current_dev(mii_dev_name) ) {
                return -1;
        }
#endif

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_ADDRESS_REG, mAddrs);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);
    
    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL1_REG, MDC_MDIO_READ_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_READ(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_DATA_READ_REG, rData);

#ifdef CONFIG_MII
        miiphy_set_current_dev(old_name);
#endif
    *rData&=0xffff;
    return 0;
}

static int register_write(u32 mAddrs, u32 rData)
{
#ifdef CONFIG_MII
        char *old_name = miiphy_get_current_dev();
        if ( miiphy_set_current_dev(mii_dev_name) ) {
                return -1;
        }
#endif

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL0_REG, MDC_MDIO_ADDR_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_ADDRESS_REG, mAddrs);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_DATA_WRITE_REG, rData);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_START_REG, MDC_MDIO_START_OP);

    MDC_MDIO_WRITE(MDC_MDIO_PREAMBLE_LEN, MDC_MDIO_DUMMY_ID, MDC_MDIO_CTRL1_REG, MDC_MDIO_WRITE_OP);

#ifdef CONFIG_MII
        miiphy_set_current_dev(old_name);
#endif

    return 0;
 }


#ifdef CONFIG_RTL8367B_SWITCH_CMD
static int phy_register_write(u32 phyNo, u32 phyAddr, u32 value)
{
	u32 regAddr;
	
  if(phyNo > PHY_INTERNALNOMAX)
        return -1;

    if(phyAddr > PHY_REGNOMAX)
        return -1;

    regAddr = 0x2000 + (phyNo << 5) + phyAddr;

    return register_write(regAddr, value);
}


static int phy_register_read(u32 phyNo, u32 phyAddr, u32 *value)
{
	u32 regAddr;

    if(phyNo > PHY_INTERNALNOMAX)
        return -1;

    if(phyAddr > PHY_REGNOMAX)
        return -1;

    regAddr = 0x2000 + (phyNo << 5) + phyAddr;

    return register_read(regAddr, value);
}
#endif

static int switch_init(void)
{
    u16      i;
    u32      init_size;
    int      retVal;

    u16 init_para[][2]= {

    {0x1303, 0x0778}, {0x1304, 0x7777}, {0x1305, 0xC010}, {0x1311, 0x1076},
    {0x1307, 0x000C},
    {0x1b00, 0x1470}, {0x1b03, 0x0222}, {0x1b24, 0x1f1f}, {0x1b25, 0x001f}, {0x1b26, 0x0004},
    };

    init_size = (sizeof(init_para) / ((sizeof(u16))*2));

    for(i = 0; i < init_size; i++)
    {
        if((retVal = register_write((u32)init_para[i][0], (u32)init_para[i][1])) != 0)
            return retVal;
    }

    printf("Switch: RTL8367RB\n");
    return 0;
}

int rtl8367b_initialize(char *name)
{
        int ret;
#ifdef CONFIG_MII
        if ( name == NULL ) {
                mii_dev_name = miiphy_get_current_dev();
                if ( mii_dev_name == NULL ) {
                        printf("RTL8367: Cannot found miiphy device, fail to initialize!\n");
                        return -1;
                }
        } else {
                mii_dev_name = name;
        }
#endif
        if ((ret = switch_init())) {
                printf("Fail to initial RTL8367B, error code %d\n", ret);
        }
        return ret;
}

#ifdef CONFIG_RTL8367B_SWITCH_CMD
int do_rtl8367_reg_rw(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[])
{
        unsigned long addr, reg, data;

        if ( argc>=4 && argv[1][0] == 'p' ) { // access PHY register
                addr = simple_strtoul(argv[2], NULL, 16);
                reg = simple_strtoul(argv[3], NULL, 16);
                if (argc>=5 && argv[1][1]=='w') { // write PHY register
                        data = simple_strtoul (argv[4], NULL, 16);
                        return phy_register_write(addr, reg, data);
                } else { // read PHY register
                        if ( !phy_register_read(addr, reg, &data) ) {
                        	printf("%04lX\n", data);
	                        return 0;
			}
                }
        } else if (argc>=3) { // access internal register
                reg = simple_strtoul(argv[2], NULL, 16);
                if (argc>=4 && argv[1][0]=='w') { // write internal register
                        data = simple_strtoul (argv[3], NULL, 16);
                        return register_write(reg, data);
                } else { // read internal register
                        if (!register_read(reg, &data)) {
                        	printf("%04lX\n", data);
                        	return 0;
			}
                }
        }

        cmd_usage(cmdtp);
        return 1;
}

U_BOOT_CMD(
        rtl8367,       5,      1,      do_rtl8367_reg_rw,
        "RTL8367 register access commands",
        "read   <reg>               - read  RT8367 register\n"
        "rtl8367 write  <reg> <data>        - write RT8367 register\n"
        "rtl8367 pread  <addr> <reg>        - read  MII PHY register\n"
        "rtl8367 pwrite <addr> <reg> <data> - write MII PHY register\n"
);
#endif // CONFIG_RTL8367B_SWITCH_CMD

