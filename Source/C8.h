#ifndef C8_H_
#define C8_H_

#include <stdio.h>
#include <stdbool.h>            //C is retarded


typedef unsigned char BYTE;     //8 bits
typedef unsigned short int WORD;//16 bits


void performopcode(WORD opcode, BYTE memory[0xFFF], BYTE register[0xF], bool display[64][32], unsigned int *delay_timer, unsigned int sound_timer, WORD stack[16], WORD *PC, WORD *SP);




#endif