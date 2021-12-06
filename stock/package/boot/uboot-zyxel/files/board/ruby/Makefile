#########################################################################

include $(TOPDIR)/config.mk

LIB	= $(obj)lib$(BOARD).a

COBJS-y	:= \
	ruby.o \
	ddr.o \
	board_cfg.o \
	timer.o \
	serial.o \
	progress.o \
	gpio.o \
	reset.o \
	intr.o \
	arasan-emac-ahb.o \
	ar8236.o \
	ar8237.o \
	info.o \
	cmd_qtnboard.o \
	uc.o \
	tftp_bootp_loop.o

COBJS-$(CONFIG_CMD_QTNBOOT) += cmd_qtnboot.o
COBJS-$(CONFIG_CMD_PCIEBOOT) += pcie.o

SOBJS-y	:= \
	vectors.o \
	flip.o \
	start.o \
	newlib_memcpy-700.o \
	newlib_memcmp.o \
	newlib_memset.o \
	newlib_io_copy.o

UC_COBJS-y := \
	muc.o \
	dsp.o

UC_SOBJS-y := \
	uc_start.o \
	muc_start.o \
	dsp_start.o

SRCS	:= $(SOBJS:.o=.S) $(COBJS-y:.o=.c) $(UC_COBJS-y:.o=.c) $(UC_SOBJS-y:.o=.S) uc_start.inl
OBJS	:= $(addprefix $(obj),$(COBJS-y))
SOBJS	:= $(addprefix $(obj),$(SOBJS-y))
UC_OBJS := $(addprefix $(obj), $(UC_COBJS-y) $(UC_SOBJS-y))

$(LIB): $(obj).depend $(OBJS) $(SOBJS) uc_objs
	$(AR) $(ARFLAGS) $@ $(OBJS) $(SOBJS) $(UC_OBJS)

u-boot.lds: u-boot.lds.S
	$(CPP) -I$(TOPDIR)/quantenna/ $(CPPFLAGS) -D__ASSEMBLY__ -P $< > $@

#########################################################################

# TODO: implement dependency to MuC/DSP code (now it is compiled each time make run)
UC_C_FLAGS = $(PLATFORM_CPPFLAGS_PATH) -I$(TOPDIR)/include -fno-builtin -ffreestanding -nostdinc -isystem $(gccincdir) -D__KERNEL__ -Os -mno-volatile-cache -mno-sdata
UC_ASM_FLAGS = $(UC_C_FLAGS) -D__ASSEMBLY__
MUC_FLAGS = -mA7
DSP_FLAGS = -mA6

ifneq ($(OBJTREE),$(SRCTREE))
UC_ASM_FLAGS += -I$(OBJTREE)/include2 -I$(OBJTREE)/include
UC_C_FLAGS += -I$(OBJTREE)/include2 -I$(OBJTREE)/include
endif

uc_objs: $(UC_COBJS-y:.o=.c) $(UC_SOBJS-y:.o=.S)
	$(CC) $(UC_ASM_FLAGS) $(DSP_FLAGS) -o $(obj)dsp_start.o dsp_start.S -c
	$(CC) $(UC_ASM_FLAGS) $(MUC_FLAGS) -o $(obj)muc_start.o muc_start.S -c
	$(CC) $(UC_ASM_FLAGS) -o $(obj)uc_start.o uc_start.S -c
	$(CC) $(UC_C_FLAGS) $(DSP_FLAFS) -o $(obj)dsp.o dsp.c -c
	$(CC) $(UC_C_FLAGS) $(MUC_FLAGS) -o $(obj)muc.o muc.c -c

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################

