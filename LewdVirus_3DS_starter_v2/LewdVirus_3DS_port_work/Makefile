ifeq ($(strip $(DEVKITPRO)),)
$(error DEVKITPRO is not set. Use devkitPro devkitARM or the GitHub Actions workflow.)
endif
include $(DEVKITPRO)/libctru/default_config
include $(DEVKITPRO)/devkitARM/base_rules
TARGET := lewdvirus_3ds_test
BUILD := build
SOURCES := source
INCLUDES := include
ARCH := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft
CFLAGS := -g -Wall -Wextra -O2 -mword-relocations -ffunction-sections $(ARCH) -D__3DS__ -Iinclude
LDFLAGS := -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS := -lctru
.PHONY: all clean
all: $(TARGET).3dsx
include $(DEVKITPRO)/devkitARM/3ds_rules
clean:
	@rm -rf $(BUILD) $(TARGET).elf $(TARGET).3dsx $(TARGET).smdh $(TARGET).elf.map
