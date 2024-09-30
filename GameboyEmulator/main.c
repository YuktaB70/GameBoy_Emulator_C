#include "GBE.h"
#include "cartridge.c"

int main(int argc, char **argv) {
    const char *rom_path = "GameboyEmulator\ROM\PokemonRed.gb";
    if (loadCartridge(rom_path)) {
        printf("Cartridge loaded successfully!\n");
        printf("Title: %s\n", cartridge.header->title);
        printf("Type: %02X\n", cartridge.header->cartType);
        printf("ROM Size: %d KB\n", (32 << cartridge.header->ROMSize));
        printf("RAM Size: %02X\n", cartridge.header->RAMSize);
        printf("License Code: %02X\n", cartridge.header->oldLic);
        printf("Version: %02X\n", cartridge.header->ROMVersion);
        return 0;
    } else {
        printf("Failed to load cartridge: %s\n", rom_path);
        return 1;
    }
}