#include <stdbool.h>
#include <SDL2/SDL.h>
#include "DisTim.h"
#include "defs.h"

bool intidisplay(C8_display* display, int SCREEN_WIDTH, int SCREEN_HEIGHT){
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER|SDL_INIT_EVENTS) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        display->win = SDL_CreateWindow( "Cruz's CHIP-8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if ( display->win == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            display->sur = SDL_GetWindowSurface( display->win );
        }

        //Create window
        display->ren = SDL_CreateRenderer(display->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if ( display->ren == NULL ){
            printf( "Render could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }

        
    }
    

    return success;
}


bool update_screen(C8_display* display)
{
    SDL_DestroyTexture(display->tex);
    display->tex = SDL_CreateTextureFromSurface(display->ren, display->fake_sur);
    SDL_FreeSurface(display->fake_sur);
    
    SDL_RenderClear(display->ren);
	//draw the texture

    SDL_RenderCopy(display->ren, display->tex, NULL, NULL);
	//Update the screen

    SDL_RenderPresent(display->ren);
	//Take a quick break after all that hard work
}

void ArrToSurface(CPU* cpu, C8_display* display){
    display->fake_sur = SDL_CreateRGBSurfaceFrom((void*)(cpu->truedisplay),
                                                            64,
                                                            32,
                                                            24,
                                                            64*3,
                                                            0xFF0000,
                                                            0x00FF00,
                                                            0x0000FF,
                                                            0x000000);
}

void DealWithDelayTimer(CPU* cpu){
    unsigned int s_timepassed = ((SDL_GetTicks()-(cpu->delay_ticks))/60);

    if(s_timepassed < (cpu->delay_timer)){
        cpu->delay_timer = (cpu->delay_timer) - s_timepassed;
    }
    else{
        cpu->delay_timer = 0;
    }
    
}

void DealWithSoundTimer(CPU* cpu){
    unsigned int s_timepassed = ((SDL_GetTicks()-(cpu->sound_ticks))/60);

    if(s_timepassed < (cpu->sound_timer)){
        cpu->sound_timer = (cpu->sound_timer) - s_timepassed;
    }
    else{
        cpu->sound_timer = 0;
    }
    
}

void shutdown(C8_display* display){
    SDL_DestroyTexture(display->tex);
    SDL_DestroyRenderer(display->ren);
    SDL_DestroyWindow(display->win);
    SDL_Quit();
}

