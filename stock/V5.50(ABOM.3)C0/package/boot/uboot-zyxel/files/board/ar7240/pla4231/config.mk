sinclude $(OBJTREE)/board/$(BOARDDIR)/config.tmp

# ROM version
ifndef TEXT_BASE
TEXT_BASE = 0x9F000000
endif

# RAM version
#TEXT_BASE = 0xA0200000

PLATFORM_CPPFLAGS := $(filter-out -march=% -mtune=%,$(PLATFORM_CPPFLAGS)) -funit-at-a-time -march=74kc -mtune=74kc
