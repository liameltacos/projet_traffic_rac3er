TARGET      := TrafficRacer
SOURCES     := source
LIBS        := -lcitro2d -lcitro3d -lctru -lm

# Chemins vers les outils
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>devkitPro")
endif

include $(DEVKITARM)/3ds_rules

# Options de compilation pour la 3DS
ARCH    := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp
CFLAGS  := -g -Wall -O2 -mword-relocations $(ARCH) -I$(DEVKITPRO)/libctru/include -I$(DEVKITPRO)/libcitro2d/include
LDFLAGS := -specs=3dsx.specs -g $(ARCH) -L$(DEVKITPRO)/libctru/lib -L$(DEVKITPRO)/libcitro2d/lib

all: $(TARGET).3dsx

$(TARGET).3dsx: $(TARGET).elf

$(TARGET).elf: $(SOURCES)/main.c
	arm-none-eabi-gcc $(CFLAGS) $(SOURCES)/main.c $(LDFLAGS) $(LIBS) -o $(TARGET).elf
