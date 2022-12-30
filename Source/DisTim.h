#ifndef _DIS_TIM_H
#define _DIS_TIM_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "C8_struct.h"
#include "defs.h"


typedef struct {
    SDL_Window *win;
    SDL_Renderer *ren;
    SDL_Texture *tex;
    SDL_Surface *sur;
    SDL_Surface *fake_sur;
    SDL_Rect *disp;
} C8_display;


bool intidisplay(C8_display* display, int SCREEN_WIDTH, int SCREEN_HEIGHT);

void ArrToSurface(CPU* cpu, C8_display* display);

bool pre_update_screen(C8_display* display);

bool update_screen(C8_display* display);

void DealWithDelayTimer(CPU* cpu);

void DealWithSoundTimer(CPU* cpu);

void shutdown(C8_display* display);


#endif