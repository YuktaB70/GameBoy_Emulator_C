
#include <stdlib.h>

typedef struct {
    unsigned char a, f;
    unsigned char b, c;
    unsigned char d, e; 
    unsigned char h, l;
    unsigned char flags; //contains 8 registers
    unsigned short pc, sp;

} CPU;

void init_cpu(CPU *Registers);
void loadProgram(const char *filename);
int runProgram(int argc, char **argv);
void execute_cycle(CPU *registers);