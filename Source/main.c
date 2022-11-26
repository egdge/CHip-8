#include "C8.h"
#include <SDL2/SDL.h>
#include <stdbool.h>        //C is retarded

//Registers and Memory
#pragma region

//Computer Memory
BYTE m_Memory[0xFFF];       //The chip-8's 0xFFF bytes of memory


//'True' Registers
BYTE r_Registers[0xF];      //The chip-8's registers V0 to VF
WORD r_AddressI;

//'Pseudo' Registers
WORD PC;                    //The 16 bit Program Counter
BYTE SP;                    //The 8 bit Stack Pointer

//Screen
bool display[64][32];

//Timers
unsigned int delay_timer;   //Decreases at a rate of 60Hz
unsigned int sound_timer;   //Make a beep when non zero, also decreases at a rate of 60Hz

//Stack Stuff
WORD stack[16];

#pragma endregion

//Initializing the CPU
bool CPUreset(FILE *in, char* f_game){
    r_AddressI=0;
    PC=0x200;
    for(int i = 0;i<16;i++){
        r_Registers[i]=0;
    }

    //Loading the file
    in = fopen( f_game, "rb" );

    //checking if the file pointer is null
    if(NULL == in){
        puts("File pinter is null");
        return 0;
    }

    fread( &m_Memory[0x200], 0xfff, 1, in);

    return 1;
}

//Get opcode
WORD getopcode(){
    WORD res = 0 ;
    res = m_Memory[PC] ; //Get
    res <<= 8 ; 
    res |= m_Memory[PC+1] ; 
    PC+=2 ;
    return res ;
}

//Print memory for debuging purposes
void printmemory(){
    for(int i = 0; i < 4096;i+=16){
            printf("%03X : ", i);
            for(int j = 0;j<16;j++){
                printf("%02X ", m_Memory[i+j]);
            }
            printf("\n");
        }
}


int main(int argc, char **argv){
    
    //Validation checks
    #pragma region
    //Check if a rom was supplied to the program
    if (argc<2){
        puts("Supply a CHIP-8 ROM");
        return 0;
    }
    

    #pragma endregion

    FILE *ROM = NULL;

    if (!CPUreset(ROM, argv[1])){
        return 0;
    }



    //Get file size
    fseek(ROM, 0, SEEK_END);
    unsigned int sz = ftell(ROM);
    rewind(ROM);
    

    //more validation
    #pragma region
     if(sz>0x400){
        puts("File larger than 1024 bytes");
        return 0;
    }
    //Check if fill size is within the limit
    #pragma endregion

    

    
    return 0;
}