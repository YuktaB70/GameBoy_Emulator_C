#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned char entry[4];
    unsigned char logo[0x33];
    unsigned char title[16];
    unsigned short newLic;
    unsigned char SGBFlag;
    unsigned char cartType;
    unsigned char ROMSize;
    unsigned char RAMSize;
    unsigned char destCode;
    unsigned char oldLic;
    unsigned char ROMVersion;
    unsigned char headerChecksum;
    unsigned short globalChecksum;




}ROMheader;

bool loadCartridge(char *cart);
