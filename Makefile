# Nom de ton jeu
TARGET      := TrafficRacer
# Dossier du code
SOURCES     := source
# Dossier des images
DATA        := gfx
# Dossier de construction
BUILD       := build
# Dossier de sortie
ROMFS       := romfs

include $(DEVKITARM)/3ds_rules

# Options de compilation
LDFLAGS     := -g -marm -mfloat-abi=hard -mfpu=vfpv2
LIBS        := -lcitro2d -lcitro3d -lctru -lm

# C'est ici que GitHub fabrique le .3dsx
all: $(TARGET).3dsx

$(TARGET).3dsx: $(TARGET).elf

$(TARGET).elf: $(SOURCES)/main.c
	@mkdir -p $(BUILD)
	$(CC) $(LDFLAGS) $(SOURCES)/main.c $(LIBS) -o $(TARGET).elf

