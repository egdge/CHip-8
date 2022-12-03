#include "C8.h"
#include <SDL2/SDL.h>
#include <stdbool.h>        //C is retarded

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 320;


//Registers and Memory
#pragma region

//Computer Memory
BYTE m_Memory[0xFFF];       //The chip-8's 0xFFF bytes of memory


//'True' Registers
BYTE r_Registers[0xF];      //The chip-8's registers V0 to VF
WORD r_AddressI;            //Mainly used to store addressess

//'Pseudo' Registers
WORD PC;                    //The 16 bit Program Counter
BYTE SP;               //The 8 bit Stack Pointer

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
    SP = -1;
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
    

    //more validation
    #pragma region
     //if(sz>0x400){
        //puts("File larger than 1024 bytes");
        //return 0;
   // }
    //Check if fill size is within the limit
    #pragma endregion

    #pragma region

    if (SDL_Init(SDL_INIT_VIDEO) != 0){
	printf("SDL_Init Error: %s\n",SDL_GetError());
    }

    SDL_Window *win = SDL_CreateWindow( "Cruz's Chip-8 Interpreter", 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SDL_WINDOWPOS_UNDEFINED, 
                        SCREEN_WIDTH, 
                        SCREEN_HEIGHT, 
                        SDL_WINDOW_SHOWN );

    if (win == NULL){
	printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
	SDL_Quit();
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL){
	SDL_DestroyWindow(win);
	printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
	SDL_Quit();
    }
    
    

    while(1){
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
        SDL_RenderClear(ren);
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0);
        SDL_Rect r;
        r.x = 0;
        r.y = 0;
        r.w = 10;
        r.h = 10;
        SDL_RenderFillRect(ren, &r);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();

    #pragma endregion


    bool play = 1;

    /*while(play){
        WORD CurrentOpcode = getopcode();
        performopcode(  CurrentOpcode, 
                        m_Memory, 
                        r_Registers, 
                        &r_AddressI, 
                        display, 
                        &delay_timer, 
                        &sound_timer, 
                        stack, 
                        &PC, 
                        &SP);
        
    }*/

    
    return 0;
}