/*
 * You need to use #ifdef around functions that may not exist
 * in the final configuration (such as i2c).
 * use a dummyfunction as first parameter to EXPORT_FUNC.
 * As an example see the CONFIG_CMD_I2C section below
 */
#ifndef EXPORT_FUNC
#define EXPORT_FUNC(a, b, c, ...)
#endif
	EXPORT_FUNC(get_version, unsigned long, get_version, void)
	EXPORT_FUNC(getc, int, getc, void)
	EXPORT_FUNC(tstc, int, tstc, void)
	EXPORT_FUNC(putc, void, putc, const char)
	EXPORT_FUNC(puts, void, puts, const char *)
	EXPORT_FUNC(printf, int, printf, const char*, ...)
#if defined(CONFIG_X86) || defined(CONFIG_PPC)
	EXPORT_FUNC(irq_install_handler, void, install_hdlr,
		    int, interrupt_handler_t, void*)

	EXPORT_FUNC(irq_free_handler, void, free_hdlr, int)
#else
	EXPORT_FUNC(dummy, void, install_hdlr, void)
	EXPORT_FUNC(dummy, void, free_hdlr, void)
#endif
	EXPORT_FUNC(malloc, void *, malloc, size_t)
	EXPORT_FUNC(free, void, free, void *)
	EXPORT_FUNC(udelay, void, udelay, unsigned long)
	EXPORT_FUNC(get_timer, unsigned long, get_timer, unsigned long)
	EXPORT_FUNC(vprintf, int, vprintf, const char *, va_list)
	EXPORT_FUNC(do_reset, int, do_reset, cmd_tbl_t *,
		    int , int , char * const [])
	EXPORT_FUNC(getenv, char  *, getenv, const char*)
	EXPORT_FUNC(setenv, int, setenv, const char *, const char *)
	EXPORT_FUNC(simple_strtoul, unsigned long, simple_strtoul,
		    const char *, char **, unsigned int)
	EXPORT_FUNC(strict_strtoul, int, strict_strtoul,
		    const char *, unsigned int , unsigned long *)
	EXPORT_FUNC(simple_strtol, long, simple_strtol,
		    const char *, char **, unsigned int)
	EXPORT_FUNC(strcmp, int, strcmp, const char *cs, const char *ct)
#if defined(CONFIG_CMD_I2C) && \
		(!defined(CONFIG_DM_I2C) || defined(CONFIG_DM_I2C_COMPAT))
	EXPORT_FUNC(i2c_write, int, i2c_write, uchar, uint, int , uchar * , int)
	EXPORT_FUNC(i2c_read, int, i2c_read, uchar, uint, int , uchar * , int)
#else
	EXPORT_FUNC(dummy, void, i2c_write, void)
	EXPORT_FUNC(dummy, void, i2c_read, void)
#endif

#if !defined(CONFIG_CMD_SPI) || defined(CONFIG_DM_SPI)
	EXPORT_FUNC(dummy, void, spi_init, void)
	EXPORT_FUNC(dummy, void, spi_setup_slave, void)
	EXPORT_FUNC(dummy, void, spi_free_slave, void)
#else
	EXPORT_FUNC(spi_init, void, spi_init, void)
	EXPORT_FUNC(spi_setup_slave, struct spi_slave *, spi_setup_slave,
		    unsigned int, unsigned int, unsigned int, unsigned int)
	EXPORT_FUNC(spi_free_slave, void, spi_free_slave, struct spi_slave *)
#endif
#ifndef CONFIG_CMD_SPI
	EXPORT_FUNC(dummy, void, spi_claim_bus, void)
	EXPORT_FUNC(dummy, void, spi_release_bus, void)
	EXPORT_FUNC(dummy, void, spi_xfer, void)
#else
	EXPORT_FUNC(spi_claim_bus, int, spi_claim_bus, struct spi_slave *)
	EXPORT_FUNC(spi_release_bus, void, spi_release_bus, struct spi_slave *)
	EXPORT_FUNC(spi_xfer, int, spi_xfer, struct spi_slave *,
		    unsigned int, const void *, void *, unsigned long)
#endif
	EXPORT_FUNC(ustrtoul, unsigned long, ustrtoul,
		    const char *, char **, unsigned int)
	EXPORT_FUNC(ustrtoull, unsigned long long, ustrtoull,
		    const char *, char **, unsigned int)
	EXPORT_FUNC(strcpy, char *, strcpy, char *dest, const char *src)
	EXPORT_FUNC(mdelay, void, mdelay, unsigned long msec)
#ifdef CONFIG_PHY_AQUANTIA
	EXPORT_FUNC(mdio_get_current_dev, struct mii_dev *,
		    mdio_get_current_dev, void)
	EXPORT_FUNC(phy_find_by_mask, struct phy_device *, phy_find_by_mask,
		    struct mii_dev *bus, unsigned phy_mask,
		    phy_interface_t interface)
	EXPORT_FUNC(mdio_phydev_for_ethname, struct phy_device *,
		    mdio_phydev_for_ethname, const char *ethname)
	EXPORT_FUNC(miiphy_set_current_dev, int, miiphy_set_current_dev,
		    const char *devname)
#endif
// add for ZyXEL zloader/multiboot
//int memcmp(const void * cs,const void * ct,size_t count)
EXPORT_FUNC(memcmp,int,memcmp,const void *,const void *,size_t)
EXPORT_FUNC(memset,void *,memset,void * ,int, size_t)
EXPORT_FUNC(memcpy,void *,memcpy,void *, const void *,size_t)
//EXPORT_FUNC(strcpy,char *,strcpy,char *, const char *)
//int do_tftpb(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
EXPORT_FUNC(do_tftpb,int,do_tftpb,cmd_tbl_t *,int,int,char * const)
EXPORT_FUNC(eth_init,int,eth_init,void)
EXPORT_FUNC(eth_halt,void,eth_halt,void)
EXPORT_FUNC(eth_rx,int,eth_rx,void)
EXPORT_FUNC(eth_set_current,void,eth_set_current,void)
//EXPORT_FUNC(NetSetHandler)
EXPORT_FUNC(getNetBootFileXferSize,ulong,getNetBootFileXferSize,void)
//EXPORT_FUNC(NetPacketInit)
//EXPORT_FUNC(lzmaBuffToBuffDecompress)
//size_t strlen(const char * s)
EXPORT_FUNC(strlen,size_t,strlen,const char *)
//int strncmp(const char * cs,const char * ct,size_t count)
EXPORT_FUNC(strncmp,int,strncmp,const char *,const char *,size_t)
//int sprintf(char *buf, const char *fmt, ...)
EXPORT_FUNC(sprintf,int,sprintf,char *,const char *, ...)
//int do_bootm(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
EXPORT_FUNC(do_bootm,int,do_bootm,cmd_tbl_t *,int,int,char * const)
//int readline (const char *const prompt);
EXPORT_FUNC(cli_readline,int,cli_readline,const char *)
//char  *get_user_command_buffer(void)
EXPORT_FUNC(get_user_command_buffer,char *,get_user_command_buffer,void)
EXPORT_FUNC(zflash_init,int,zflash_init,void)
//int zflash_read(unsigned long offs, unsigned long len, char *buf)
EXPORT_FUNC(zflash_read,int,zflash_read,unsigned long ,unsigned long ,char *)
//int zflash_write(unsigned long offs, unsigned long len, char *buf)
EXPORT_FUNC(zflash_write,int,zflash_write,unsigned long ,unsigned long ,char *)
//int zflash_erase(unsigned long offs, unsigned long len)
EXPORT_FUNC(zflash_erase,int,zflash_erase,unsigned long,unsigned long)
EXPORT_FUNC(znand_init,int,znand_init,void)
//int znand_read(unsigned long offs, unsigned long len, char *buf)
EXPORT_FUNC(znand_read,int,znand_read,unsigned long ,unsigned long ,char *)
EXPORT_FUNC(znand_write,int,znand_write,unsigned long ,unsigned long ,char *)
EXPORT_FUNC(znand_erase,int,znand_erase,unsigned long,unsigned long)
EXPORT_FUNC(saveenv,int,saveenv,void)
//int do_run(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
EXPORT_FUNC(do_run,int,do_run,cmd_tbl_t *,int,int,char *)
//int run_command(const char *cmd, int flag)
EXPORT_FUNC(run_command,int,run_command,const char *,int)
//void flush_cache(ulong start_addr, ulong size);
EXPORT_FUNC(flush_cache,void,flush_cache,ulong,ulong)
//int image_check_hcrc(const image_header_t *hdr)
EXPORT_FUNC(image_check_hcrc,int,image_check_hcrc,const image_header_t *)
//int image_check_dcrc(const image_header_t *hdr)
EXPORT_FUNC(image_check_dcrc,int,image_check_dcrc,const image_header_t *)
EXPORT_FUNC(clear_ctrlc,void,clear_ctrlc,void)
EXPORT_FUNC(configure_pio,int,configure_pio,int,int)
EXPORT_FUNC(set_pio,int,set_pio,int,int)
//int get_pio(int pio, int *level)
EXPORT_FUNC(get_pio,int,get_pio,int,int *)
EXPORT_FUNC(max_pio_num,int,max_pio_num,void)
EXPORT_FUNC(net_init,void,net_init,void)
EXPORT_FUNC(eth_initialize,int,eth_initialize,void)