ifneq ($(strip $(DEVKITARM)),)
include $(DEVKITARM)/3ds_rules
endif

TARGET      := TrafficRacer
export INCLUDE := $(DEVKITPRO)/libctru/include $(DEVKITPRO)/libcitro2d/include $(DEVKITPRO)/libcitro3d/include
export LIBPATHS := $(DEVKITPRO)/libctru/lib $(DEVKITPRO)/libcitro2d/lib $(DEVKITPRO)/libcitro3d/lib

ARCH    := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp
CFLAGS  := -g -Wall -O2 -mword-relocations $(ARCH) $(foreach dir,$(INCLUDE),-I$(dir))
LDFLAGS := -specs=3dsx.specs -g $(ARCH) $(foreach dir,$(LIBPATHS),-L$(dir))
LIBS    := -lcitro2d -lcitro3d -lctru -lm

all: $(TARGET).3dsx

$(TARGET).3dsx: $(TARGET).elf

$(TARGET).elf: source/main.c
	arm-none-eabi-gcc $(CFLAGS) source/main.c $(LDFLAGS) $(LIBS) -o $(TARGET).elf
