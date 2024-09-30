#include "GBE.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MEMORY_SIZE 0x10000 // Total memory (64KB for Game Boy)
#define ROM_SIZE 0x8000     // ROM size (32KB typical)

unsigned char memory[MEMORY_SIZE];
unsigned char *rom;


void init_cpu(CPU *registers) {
    registers->a = 0;
    registers->f = 0;
    registers->b = 0;
    registers->c = 0;
    registers->d = 0;
    registers->e = 0;
    registers->h = 0;
    registers->l = 0;
    registers->sp = 0xFFFE;
    registers->pc = 0x0100;

    memset(memory, 0, MEMORY_SIZE);
    rom = NULL; 

};

void loadProgram(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if(file ==  NULL) {
        printf("File cannot be opened");
        exit(1);
    }
    else {
        fread(memory, 1, ROM_SIZE, file); //reads data ROM_SIZE bytes of data into memory
        fclose(file); //closes file
    }
};


int runProgram(int argc, char **argv) {

}