#ifndef C8_H_
#define C8_H_

#include <stdio.h>
#include <stdbool.h>            //C is retarded


typedef unsigned char BYTE;     //8 bits
typedef unsigned short int WORD;//16 bits

/*
void performopcode(WORD opcode){
    switch (opcode & 0xF000)
    {
    case (0x0000):
        switch (opcode & 0x0FFF)
        {
        case 0x00EE:
            o_cls();
            break;

        case 0x000E:
            o_ret();
            break;

        default:
            jmp();
            break;
        }
        break;

    default:
        break;
    }
}
*/


#endif C8_H_