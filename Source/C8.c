#include "C8.h"
#include <stdlib.h>


void PerformOpcode( WORD opcode, 
                    BYTE memory[0xFFF], 
                    BYTE mregister[0xF], 
                    WORD* AddressI, 
                    bool display[64][32], 
                    unsigned int *delay_timer, 
                    unsigned int *sound_timer, 
                    WORD stack[16], 
                    WORD *PC, 
                    WORD *SP)
{
    
    switch (opcode & 0xFFFF)
    {
    case (0x0000)://JMP, Clear Screen, Return Subroutine
        switch (opcode & 0x0FFF)
        {
        case 0x00EE: //Unconditional Jump
            *PC = stack[*SP];
            --(*SP);
            break;

        case 0x00E0: //Clear the screen
            for (int i = 0; i < 64; i++)
            {
                for (size_t j = 0; j < 32; j++)
                {
                    display[1][j] = 0;
                }
                
            }
            break;

        default: //Uncodtional Jump
            *PC = (opcode & 0x0FFF);
            break;
        }
        break;

    case (0x1000)://JMP
        *PC = (opcode & 0x0FFF);
        break;
    
    case (0x2000)://Call subroutine
        ++(*SP);
        stack[*SP] = *SP;
        *PC = (opcode & 0x0FFF);
        break;
    
    case (0x3000)://Skip next instruction if V[x] == lower byte
        if( mregister[(opcode & 0x0F00)>>8] == (opcode & 0x00FF) ){
                *PC = (*PC) + 2;
        }
        break;
    
    case (0x4000)://Skip next instruction if V[x] != lower byte
        if( mregister[(opcode & 0x0F00)>>8] != (opcode & 0x00FF) ){
                *PC = (*PC) + 2;
        }
        break;
    
    case (0x5000)://Skip next instruction if V[x]=V[y]
        if( mregister[(opcode & 0x0F00)>>8] == mregister[(opcode & 0x00F0)>>4] ){
                *PC = (*PC) + 2;
        }
        break;
    
    case (0x6000)://Places bottom byte in V[x]
        mregister[(opcode & 0x0F00)>>8] = (opcode & 0x00FF);
        break;

    case (0x7000)://Add V[x] to the bottom 2 bytes
        mregister[(opcode & 0x0F00)>>8] += (opcode & 0x00FF);
        break;
    
    case (0x8000):
        switch (opcode & 0x000F){
        case 0x0000://Set V[x] as V[y]
            mregister[(opcode & 0x0F00)>>8] = mregister[(opcode & 0x00F0)>>4];
            break;

        case 0x0001://Set V[x] = V[x] OR V[y]
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) | (mregister[(opcode & 0x00F0)>>4]));
            break;
        
        case 0x0002://Set V[x] = V[x] AND V[y]
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) & (mregister[(opcode & 0x00F0)>>4]));
            break;

        case 0x0003://Set V[x] = V[x] XOR V[y]
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) ^ (mregister[(opcode & 0x00F0)>>4]));
            break;

        case 0x0004://Set Vx = Vx + Vy, set VF = carry
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) + (mregister[(opcode & 0x00F0)>>4]));
            if(mregister[(opcode & 0x00F0) >> 4] > (0xFF - mregister[(opcode & 0x0F00) >> 8])){
                        mregister[0xF] = 1; //carry
                    }
                    else{
                        mregister[0xF] = 0;
                    }
            break;

        case 0x0005://Set Vx = Vx - Vy, set VF = NOT borrow  
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) - (mregister[(opcode & 0x00F0)>>4]));
            if(mregister[(opcode & 0x0F00) >> 8] > (mregister[(opcode & 0x00F0)>>4])){
                        mregister[0xF] = 1; //Not borrow
                    }
                    else{
                        mregister[0xF] = 0;
                    }
            break;

        case 0x0006://Set Vx = Vx SHR 1
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) >>1);
            if((mregister[(opcode & 0x0F00) >> 8] & 0x0001) == 1){
                        mregister[0xF] = 1;//least-significant bit of Vx is 1
                    }
                    else{
                        mregister[0xF] = 0;
                    }
            break;

        case 0x0007://Set Vx = Vy - Vx, set VF = NOT borrow
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x00F0)>>4]) - (mregister[(opcode & 0x0F00)>>8]));
            if(mregister[(opcode & 0x00F0) >> 4] > (mregister[(opcode & 0x0F00) >> 8])){
                        mregister[0xF] = 1; //Not borrow
                    }
                    else{
                        mregister[0xF] = 0;
                    }
            break;

        case 0x000E://Set Vx = Vx SHL 1
            mregister[(opcode & 0x0F00)>>8] = ((mregister[(opcode & 0x0F00)>>8]) << 1);
            if((mregister[(opcode & 0x0F00) >> 8] & 0x8000) == 0x8000){
                        mregister[0xF] = 1;//most-significant bit of Vx is 1
                    }
                    else{
                        mregister[0xF] = 0;
                    }
            break;

        default://Error case
            puts("Invalid Opcode");
            break;
        }
        break;
    
    case (0x9000)://Skip next instruction if Vx != Vy
        if( mregister[(opcode & 0x0F00)>>8] != mregister[(opcode & 0x00F0)>>4] ){
                *PC = (*PC) + 2;
        }
        break;

    case (0xA000)://Set I = nnn
        *AddressI = (opcode & 0x0FFF);
        break;

    case (0xB000)://Jump to location nnn + V0
        *PC = (opcode & 0x0FFF);
        break;

    case (0xC000):
        mregister[(opcode & 0x0F00)>>8] = ((rand() % (0xFF + 1)) & (opcode & 0x00FF));
        break;

    case (0xD000):{
            
        }
        break;

    case (0xE000):
        break;

    case (0xF000):
        break;

    default:
        break;
    }
}
