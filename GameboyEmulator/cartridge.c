#include "cartridge.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char filename[1024];
    unsigned long rom_size; 
    unsigned char *rom;
    ROMheader *header;
} Cartridge;

static Cartridge cartridge;


//STORES THE TYPE OF ROMS 
static const char *ROM_TYPES[] = {
    "ROM ONLY",
    "MBC1",
    "MBC1+RAM",
    "MBC1+RAM+BATTERY",
    "0x04 ???",
    "MBC2",
    "MBC2+BATTERY",
    "0x07 ???",
    "ROM+RAM 1",
    "ROM+RAM+BATTERY 1",
    "0x0A ???",
    "MMM01",
    "MMM01+RAM",
    "MMM01+RAM+BATTERY",
    "0x0E ???",
    "MBC3+TIMER+BATTERY",
    "MBC3+TIMER+RAM+BATTERY 2",
    "MBC3",
    "MBC3+RAM 2",
    "MBC3+RAM+BATTERY 2",
    "0x14 ???",
    "0x15 ???",
    "0x16 ???",
    "0x17 ???",
    "0x18 ???",
    "MBC5",
    "MBC5+RAM",
    "MBC5+RAM+BATTERY",
    "MBC5+RUMBLE",
    "MBC5+RUMBLE+RAM",
    "MBC5+RUMBLE+RAM+BATTERY",
    "0x1F ???",
    "MBC6",
    "0x21 ???",
    "MBC7+SENSOR+RUMBLE+RAM+BATTERY",
};

static const char *LIC_CODE[0xA5] = {
    [0x00] = "None",
    [0x01] = "Nintendo R&D1",
    [0x08] = "Capcom",
    [0x13] = "Electronic Arts",
    [0x18] = "Hudson Soft",
    [0x19] = "b-ai",
    [0x20] = "kss",
    [0x22] = "pow",
    [0x24] = "PCM Complete",
    [0x25] = "san-x",
    [0x28] = "Kemco Japan",
    [0x29] = "seta",
    [0x30] = "Viacom",
    [0x31] = "Nintendo",
    [0x32] = "Bandai",
    [0x33] = "Ocean/Acclaim",
    [0x34] = "Konami",
    [0x35] = "Hector",
    [0x37] = "Taito",
    [0x38] = "Hudson",
    [0x39] = "Banpresto",
    [0x41] = "Ubi Soft",
    [0x42] = "Atlus",
    [0x44] = "Malibu",
    [0x46] = "angel",
    [0x47] = "Bullet-Proof",
    [0x49] = "irem",
    [0x50] = "Absolute",
    [0x51] = "Acclaim",
    [0x52] = "Activision",
    [0x53] = "American sammy",
    [0x54] = "Konami",
    [0x55] = "Hi tech entertainment",
    [0x56] = "LJN",
    [0x57] = "Matchbox",
    [0x58] = "Mattel",
    [0x59] = "Milton Bradley",
    [0x60] = "Titus",
    [0x61] = "Virgin",
    [0x64] = "LucasArts",
    [0x67] = "Ocean",
    [0x69] = "Electronic Arts",
    [0x70] = "Infogrames",
    [0x71] = "Interplay",
    [0x72] = "Broderbund",
    [0x73] = "sculptured",
    [0x75] = "sci",
    [0x78] = "THQ",
    [0x79] = "Accolade",
    [0x80] = "misawa",
    [0x83] = "lozc",
    [0x86] = "Tokuma Shoten Intermedia",
    [0x87] = "Tsukuda Original",
    [0x91] = "Chunsoft",
    [0x92] = "Video system",
    [0x93] = "Ocean/Acclaim",
    [0x95] = "Varie",
    [0x96] = "Yonezawa/s’pal",
    [0x97] = "Kaneko",
    [0x99] = "Pack in soft",
    [0xA4] = "Konami (Yu-Gi-Oh!)"
};

const char* getLic() {
    if (cartridge.header->newLic <= 0xA4) {
        return LIC_CODE[cartridge.header->oldLic];
    }
    else {
        return "License not found";
    }
};
const char *getCartType() {
    if (cartridge.header->cartType <= 0x22 ) {
        return LIC_CODE[cartridge.header->cartType];
    }
    else {
        return "Cart not found";
    }
};

bool loadCartridge(char *cart) {
    //copy file safetly into cartridge filename
    snprintf(cartridge.filename, sizeof(cartridge.filename), "%s", cart );
    //open file
    FILE *fp = fopen(cart, "rb");
    if (fp == NULL) {
        return false;
    }
    //Get file size and allocate memory for it
    fseek(fp, 0, SEEK_END); //Movies file pointer to end of file to determine size
    cartridge.rom_size = ftell(fp); //returns current position of pointer
    rewind(fp); //resets the pointer back to the beginning of file

    cartridge.rom = malloc(cartridge.rom_size);
    if (cartridge.rom == NULL) {
        fclose(fp);
        return false;
    }

    fread(cartridge.rom, 1, cartridge.rom_size, fp); //read file into rom data
    fclose(fp);

    cartridge.header = (ROMheader *)(cartridge.rom + 0x100); //make sure pointer is point to 0x100
    cartridge.header->title[15] = '\0';

        printf("Cartridge Loaded:\n");
    printf("\t Title    : %s\n", cartridge.header->title);
    printf("\t ROM Size : %d KB\n", (32 << cartridge.header->RAMSize));
    printf("\t RAM Size : %02X\n", cartridge.header->RAMSize);
    printf("\t ROM Vers : %02X\n", cartridge.header->ROMVersion);

    unsigned short checksum = 0;
    for (unsigned short i = 0x0134; i <= 0x014C; i++) {
        checksum = checksum - cartridge.rom[i] - 1;
    }
    printf("\t Checksum : %02X (%s)\n", cartridge.header->headerChecksum, (checksum & 0xFF) ? "PASSED" : "FAILED");

    return true;

};
