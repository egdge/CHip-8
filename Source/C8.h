#ifndef C8_H
#define C8_H


#include <stdio.h>
#include <string.h>
#include <stdbool.h>            //C is retarded
#include "defs.h"
#include "C8_struct.h"

WORD getX(WORD opc);

WORD getY(WORD opc);

WORD getN(WORD opc);

WORD getNNN(WORD opc);

void PerformOpcode( WORD opcode, 
                    CPU *CPUC8);

bool CPUINIT(CPU *C8CPU, FILE *in, char* f_game);

WORD getopcode(CPU *CPU8);


#endif