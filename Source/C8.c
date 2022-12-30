#include "C8.h"
#include "C8_struct.h"
#include "DisTim.h"
#include "defs.h"
#include <string.h>
#include <stdlib.h>

#define R_VALUE 0x00
#define G_VALUE 0xCC
#define B_VALUE 0x66 

WORD getX(WORD opc){
    return ((opc & 0x0F00) >> 8);
}

WORD getY(WORD opc){
    return ((opc & 0x00F0) >> 4);
}

WORD getN(WORD opc){
    return (opc & 0x000F);
}

WORD getNNN(WORD opc){
    return (opc & 0x0FFF);
}

WORD getKK(WORD opc){
    return (opc & 0x00FF);
}

BYTE C8_font[] = 
{
    0xF0, 0x90, 0x90, 0x90, 0xF0,		// 0
	0x20, 0x60, 0x20, 0x20, 0x70,		// 1
	0xF0, 0x10, 0xF0, 0x80, 0xF0,		// 2
	0xF0, 0x10, 0xF0, 0x10, 0xF0,		// 3
	0x90, 0x90, 0xF0, 0x10, 0x10,		// 4
	0xF0, 0x80, 0xF0, 0x10, 0xF0,		// 5
	0xF0, 0x80, 0xF0, 0x90, 0xF0,		// 6
	0xF0, 0x10, 0x20, 0x40, 0x40,		// 7
	0xF0, 0x90, 0xF0, 0x90, 0xF0,		// 8
	0xF0, 0x90, 0xF0, 0x10, 0xF0,		// 9
	0xF0, 0x90, 0xF0, 0x90, 0x90,		// A
	0xE0, 0x90, 0xE0, 0x90, 0xE0,		// B
	0xF0, 0x80, 0x80, 0x80, 0xF0,		// C
	0xE0, 0x90, 0x90, 0x90, 0xE0,		// D
	0xF0, 0x80, 0xF0, 0x80, 0xF0,		// E
	0xF0, 0x80, 0xF0, 0x80, 0x80		// F
};

//Initializing the CPU
bool CPUINIT(CPU *C8CPU,FILE *in, char* f_game){
    C8CPU->r_AddressI=0;
    C8CPU->PC=0x200;
    C8CPU->SP = 0;
    C8CPU->close = 0;
    
    
    memset(C8CPU->r_Registers,0, sizeof(C8CPU->r_Registers) / sizeof(BYTE));
    memset(C8CPU->m_Memory,0, sizeof(C8CPU->m_Memory)/sizeof(BYTE));
    memset(C8CPU->display,0, sizeof(C8CPU->display)/sizeof(BYTE));
    memset(C8CPU->truedisplay,0, sizeof(C8CPU->truedisplay)/sizeof(BYTE));

    for(int i = 0;i<80;i++){
        C8CPU->m_Memory[i]=C8_font[i];
    }
    

    //Loading the file
    in = fopen( f_game, "rb" );

    //checking if the file pointer is null
    if(NULL == in){
        puts("File pinter is null");
        return 0;
    }

    fread( ((C8CPU->m_Memory)+0x200), 0xfff, 1, in);

    return 1;
}

//Get opcode
WORD getopcode(CPU *C8CPU){
    WORD res = 0 ;
    res = C8CPU->m_Memory[C8CPU->PC] ; //Get
    res <<= 8 ; 
    res |= C8CPU->m_Memory[(C8CPU->PC)+1] ; 
    return res ;
}


void PerformOpcode( WORD opcode, 
                    CPU *CPUC8){
    WORD X = getX(opcode);
    WORD Y= getY(opcode);
    WORD N = getN(opcode);
    WORD NNN = getNNN(opcode);
    WORD KK = getKK(opcode);
    bool pcincf = 0;

    switch (opcode & 0xF000)
    {
    case (0x0000)://JMP, Clear Screen, Return Subroutine
        switch (opcode & 0x0FFF)
        {
        case 0x00EE: //Return Subroutine
            CPUC8->PC = CPUC8->stack[(CPUC8->SP) - 1];
            if(CPUC8->SP == 0){
                CPUC8->SP = 0xF;
            }
            else{
                --(CPUC8->SP);
            }
            pcincf = 1;
            break;

        case 0x00E0: //Clear the screen
            memset(CPUC8->display,0, sizeof(CPUC8->display)/sizeof(BYTE));
            memset(CPUC8->truedisplay,0, sizeof(CPUC8->truedisplay)/sizeof(BYTE));
            CPUC8->draw = 1;
            break;

        default: //Uncodtional Jump
            CPUC8->PC = NNN;
            pcincf = 1;
            break;
        }
        break;

    case (0x1000)://JMP
        CPUC8->PC = NNN;
        pcincf = 1;
        break;
    
    case (0x2000)://Call subroutine
        CPUC8->stack[CPUC8->SP] = CPUC8->PC + 2;
        if(CPUC8->SP == 0x10){
                CPUC8->SP = 0x0;
            }
            else{
                ++(CPUC8->SP);
            }
        CPUC8->PC = NNN;
        pcincf = 1;
        break;
    
    case (0x3000)://Skip next instruction if V[x] == lower byte
        if( CPUC8->r_Registers[X] == (KK) ){
                CPUC8->PC = (CPUC8->PC) + 2;
        }
        break;
    
    case (0x4000)://Skip next instruction if V[x] != lower byte
        if( CPUC8->r_Registers[X] != (KK) ){
                CPUC8->PC = (CPUC8->PC) + 2;
        }
        break;
    case (0x5000)://Skip next instruction if V[x]=V[y]
        if( CPUC8->r_Registers[X] == CPUC8->r_Registers[Y] ){
                CPUC8->PC = (CPUC8->PC) + 2;
        }
        break;
    
    case (0x6000)://Places bottom byte in V[x]
        CPUC8->r_Registers[X] = (KK);
        break;

    case (0x7000)://Add V[x] to the bottom 2 bytes
        CPUC8->r_Registers[X] += KK;
        break;
    
    case (0x8000)://
            switch (opcode & 0x000F){
                case 0x0000://Set V[x] as V[y]
                    CPUC8->r_Registers[X] = CPUC8->r_Registers[Y];
                    break;

                case 0x0001://Set V[x] = V[x] OR V[y]
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) | (CPUC8->r_Registers[Y]));
                    CPUC8->r_Registers[0xF] = 0;
                    break;
                
                case 0x0002://Set V[x] = V[x] AND V[y]
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) & (CPUC8->r_Registers[Y]));
                    CPUC8->r_Registers[0xF] = 0;
                    break;

                case 0x0003://Set V[x] = V[x] XOR V[y]
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) ^ (CPUC8->r_Registers[Y]));
                    CPUC8->r_Registers[0xF] = 0;
                    break;

                case 0x0004://Set Vx = Vx + Vy, set VF = carry
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) + (CPUC8->r_Registers[Y]));

                    if(CPUC8->r_Registers[(opcode & 0x00F0) >> 4] > (0xFF - CPUC8->r_Registers[(opcode & 0x0F00) >> 8])){
                        CPUC8->r_Registers[0xF] = 1; //carry
                    }
                    else{
                        CPUC8->r_Registers[0xF] = 0;
                    }
                    break;

                case 0x0005://Set Vx = Vx - Vy, set VF = NOT borrow  
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) - (CPUC8->r_Registers[Y]));

                    if(CPUC8->r_Registers[(opcode & 0x0F00) >> 8] > (CPUC8->r_Registers[Y])){
                        CPUC8->r_Registers[0xF] = 1; //Not borrow
                    }
                    else{
                        CPUC8->r_Registers[0xF] = 0;
                    }
                    break;

                case 0x0006://Set Vx = Vx SHR 1
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) >>1);

                    if((CPUC8->r_Registers[(opcode & 0x0F00) >> 8] & 0x0001) == 1){
                        CPUC8->r_Registers[0xF] = 1;//least-significant bit of Vx is 1
                    }
                    else{
                        CPUC8->r_Registers[0xF] = 0;
                    }
                    break;

                case 0x0007://Set Vx = Vy - Vx, set VF = NOT borrow
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[Y]) - (CPUC8->r_Registers[X]));

                    if(CPUC8->r_Registers[(opcode & 0x00F0) >> 4] > (CPUC8->r_Registers[(opcode & 0x0F00) >> 8])){
                        CPUC8->r_Registers[0xF] = 1; //Not borrow
                    }
                    else{
                        CPUC8->r_Registers[0xF] = 0;
                    }
                    break;

                case 0x000E://Set Vx = Vx SHL 1
                    CPUC8->r_Registers[X] = ((CPUC8->r_Registers[X]) << 1);

                    if((CPUC8->r_Registers[(opcode & 0x0F00) >> 8] & 0x8000) == 0x8000){
                        CPUC8->r_Registers[0xF] = 1;//most-significant bit of Vx is 1
                    }
                    else{
                        CPUC8->r_Registers[0xF] = 0;//most-significant bit of Vx is 0
                    }
                    break;

                default://Error case
                    puts("Invalid Opcode 1");
                    break;
            }
        break;
    
    case (0x9000)://Skip next instruction if Vx != Vy
        if( CPUC8->r_Registers[X] != CPUC8->r_Registers[Y] ){
            CPUC8->PC = (CPUC8->PC) + 2;
        }
        break;

    case (0xA000)://Set I = nnn
        CPUC8->r_AddressI = NNN;
        break;

    case (0xB000)://Jump to location nnn + V0
        CPUC8->PC = NNN + CPUC8->r_Registers[0x0];
        pcincf = 1;
        break;

    case (0xC000):
        CPUC8->r_Registers[X] = ((rand() % (0xFF + 1)) & (KK));
        break;

    case (0xD000):
        CPUC8->r_Registers[0xF] = 0;
        BYTE height = N;
        BYTE pixel;
        BYTE xpos;
        BYTE ypos;
        if (CPUC8->r_Registers[X] > 63){xpos = CPUC8->r_Registers[X]%64;}
        else {xpos = CPUC8->r_Registers[X];}
        if (CPUC8->r_Registers[Y] > 31){ypos = CPUC8->r_Registers[Y]%32;}
        else {ypos = CPUC8->r_Registers[Y];}


        for (int yline = 0; yline < height; yline++)
            {
                pixel = CPUC8->m_Memory[(CPUC8->r_AddressI) + yline];
                for(int xline = 0; xline < 8; xline++)
                {   
                    if((pixel & (0x80 >> xline)) != 0)
                    {
                        if(CPUC8->display[(xpos + xline + ((ypos + yline) * 64))] == 1)
                        {
                            CPUC8->r_Registers[0xF] = 1;
                        }
                        CPUC8->display[xpos + xline + ((ypos + yline) * 64)] ^= 1;
                    }
                }
            }
        


        CPUC8->draw = 1;
        break;

    case (0xE000):
        switch (opcode & 0x00FF)
        {
        case 0x009E:
            if(CPUC8->Key[CPUC8->r_Registers[X]]){
                CPUC8->PC = CPUC8->PC + 2;
            } 
            break;
            
        case 0x00A1:
            if(!CPUC8->Key[CPUC8->r_Registers[X]]){
                CPUC8->PC = CPUC8->PC + 2;
            }
            break;

        default:
            printf("Invalid Opcode 3");
            break;
        }
        break;

    case (0xF000):
        switch (opcode & 0x00FF){
        case 0x0007:
            CPUC8->r_Registers[X] = CPUC8->delay_timer;
            break;
        
        case 0x000A:
            bool key_pressed = false;

            pcincf = 1;

            for(int i = 0; i < 16; ++i)
            {
                if(CPUC8->Key[i] != 0)
                {
                    CPUC8->r_Registers[X] = i;

                    pcincf = 0;
                }
            }
            
            break;
        
        case 0x0015:
            CPUC8->delay_timer = CPUC8->r_Registers[X];
            break;
        
        case 0x0018:
            CPUC8->sound_timer = CPUC8->r_Registers[X];
            break;
        
        case 0x001E:
            CPUC8->r_AddressI = CPUC8->r_AddressI + CPUC8->r_Registers[X];
            break;

        case 0x0029:
            CPUC8->r_AddressI = (CPUC8->r_Registers[X] * 5);
            break;

        case 0x0033:
            CPUC8->m_Memory[CPUC8->r_AddressI] = (CPUC8->r_Registers[X]/100);
            CPUC8->m_Memory[(CPUC8->r_AddressI)+1] = (CPUC8->r_Registers[X]/10)%10;
            CPUC8->m_Memory[(CPUC8->r_AddressI)+2] = (CPUC8->r_Registers[X]%10);
            break;

        case 0x0055:
            for(int i = 0 ; i < (X+1); i++){
                CPUC8->m_Memory[(CPUC8->r_AddressI) + i] = CPUC8->r_Registers[i];
            }
            CPUC8->r_AddressI = CPUC8->r_AddressI + X + 1;
            break;

        case 0x0065:
            for(int i = 0 ; i < (X+1); i++){
                CPUC8->r_Registers[i] = CPUC8->m_Memory[(CPUC8->r_AddressI) + i];
            }
            CPUC8->r_AddressI = CPUC8->r_AddressI + X + 1;
            break;

        default:
            break;
        }
        break;

    
    default:
        printf(" %X Invalid Opcode 4\n", opcode);
        break;
    }
    if(!pcincf){
        CPUC8->PC += 2;
    }

}


