#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "chip8.h"


Chip8 chip8; 


void init() {
    chip8.memory = (unsigned char *)malloc(4096 * sizeof(unsigned char));
    chip8.stack = (unsigned char *)malloc(16 *sizeof(unsigned char));
    chip8.display = (unsigned char *)malloc(64 * 32 * sizeof(unsigned char));
    
    if(!chip8.memory || !chip8.stack || !chip8.display) {
        printf("Memory Allocation failed");
    }

    //Ensure that registers and memory are initalized to 0
    for (int i = 0; i < 16; i++) {
        chip8.V[i] = 0;
        chip8.keys[i] = 0;
    }
    for (int i = 0; i < 4096; i++) {
        chip8.memory[i] = 0;
    }

    chip8.PC = 0x200;
    chip8.AP = 0x0;
    chip8.SP = 0;
    chip8.delay_timer = 0;
    chip8.sounds_timer = 0;
};