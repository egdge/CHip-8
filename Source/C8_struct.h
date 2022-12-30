#ifndef C8_STRUCT_H
#define C8_STRUCT_H

#include "defs.h"
#include <stdbool.h>

typedef struct{
    //Computer Memory
    BYTE m_Memory[0x1000];       //The chip-8's 0xFFF(4096) bytes of memory


    //'True' Registers
    BYTE r_Registers[0x10];      //The chip-8's registers V0 to VF
    WORD r_AddressI;            //Mainly used to store addressess

    //'Pseudo' Registers
    WORD PC;                    //The 16 bit Program Counter
    BYTE SP;               //The 8 bit Stack Pointer

    //Screen
    BYTE display[2048];
    BYTE truedisplay[2048 * 3];
    bool draw;


    //Timers
    unsigned int delay_ticks;   //The amount of ticks present when delay timer is initialized
    unsigned int sound_ticks;   //The amount of ticks present when delay timer is initialized
    unsigned int delay_timer;   //Decreases at a rate of 60Hz
    unsigned int sound_timer;   //Make a beep when non zero, also decreases at a rate of 60Hz

    //Stack Stuff
    WORD stack[16];

    //Key being pressed
    BYTE Key[16];
    BYTE close;
} CPU;

#endif