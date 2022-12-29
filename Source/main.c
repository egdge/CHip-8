#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>        //C is retarded
#include "C8.h"
#include "C8_struct.h"
#include "DisTim.h"
#include "Input.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;

#define R_VALUE 0x00
#define G_VALUE 0x2A
#define B_VALUE 0xFF 

//Print memory for debuging purposes
void printmemory(CPU *C8CPU);
void printdisplay(CPU *C8CPU);

WORD opcode;

CPU Main_CPU;
C8_display Main_Display;


int main(int argc, char **argv){
    

    //Check if a rom was supplied to the program
    if (argc<2){
        puts("Supply a CHIP-8 ROM");
        return 0;
    }

    FILE *ROM = NULL;
    
    if (!CPUINIT(&Main_CPU,ROM, argv[1])){
        return 0;
    }

    if(!init(&Main_Display, SCREEN_WIDTH, SCREEN_HEIGHT)){
        return 0;
    }

    int cycles = 0;

    
    while(1){

        //Get Opcode
        opcode = getopcode(&Main_CPU);
        printf("cycle: %d\nPC: %04X\ninstrustion: %04X\n",cycles, Main_CPU.PC, opcode);
       
        
        PerformOpcode(opcode, &Main_CPU);
        

        //Handle timers
        DealWithDelayTimer(&Main_CPU);
        DealWithSoundTimer(&Main_CPU);

        //Handle Display
        if(Main_CPU.draw){
            
            for(int i = 0; i<2048; i++){
                if(Main_CPU.display[i]){
                    Main_CPU.truedisplay[i * 3]   = B_VALUE;
                    Main_CPU.truedisplay[(i * 3)+1] = G_VALUE;
                    Main_CPU.truedisplay[(i * 3)+2] = R_VALUE;
                }
                else{
                    Main_CPU.truedisplay[i * 3]   = 0x00;
                    Main_CPU.truedisplay[(i * 3)+1] = 0x00 ;
                    Main_CPU.truedisplay[(i * 3)+2] = 0x00;
                }
                
            }
            ArrToSurface(&Main_CPU, &Main_Display);

            update_screen(&Main_Display);
            Main_CPU.draw = 0;
        }

        //Handle Sound

        ++cycles;
        SDL_Delay(1000);

    }
    
    

    
    
    return 0;
}

void printmemory(CPU *C8CPU){
    for(int i = 0; i < 4096;i+=16){
            printf("%03X : ", i);
            for(int j = 0;j<16;j++){
                printf("%02X ", Main_CPU.m_Memory[i+j]);
            }
            printf("\n");
        }
}

void printdisplay(CPU *C8CPU){
    printf("\n");
    for(int i = 0; i < 2048;i+=16){
            printf("%03X : ", i);
            for(int j = 0;j<16;j++){
                printf("%02X ", Main_CPU.display[i+j]);
            }
            printf("\n");
        }
}