#include <stdlib.h>


typedef struct {
    unsigned char *memory; //memory 4KB
    unsigned char AP;
    unsigned char PC; // program counter
    unsigned char V[16]; //program counter
    unsigned char *stack;
    int SP;  //stacker pointer
    unsigned char delay_timer;
    unsigned char sounds_timer; 

    unsigned char keys[16]; //16 keys
    unsigned char *display; //display buffer(64x32 pixels)

} Chip8;


void init();
void run();
void loadProgram(const char* filename);
