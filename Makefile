# Chemin vers le compilateur
CC          := /opt/devkitpro/devkitARM/bin/arm-none-eabi-gcc

# Nom du fichier de sortie
TARGET      := TrafficRacer

# Bibliothèques à utiliser
LIBS        := -lcitro2d -lcitro3d -lctru -lm

# Options de compilation
ARCH        := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mfpu=vfp
CFLAGS      := -g -Wall -O2 -mword-relocations $(ARCH)
LDFLAGS     := -specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(TARGET).map

# Commande par défaut
all: $(TARGET).3dsx

$(TARGET).3dsx: $(TARGET).elf

$(TARGET).elf: source/main.c
	$(CC) $(CFLAGS) source/main.c $(LDFLAGS) $(LIBS) -o $(TARGET).elf
