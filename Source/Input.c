#include "Input.h"
#include <SDL2/SDL.h>

void C8_getInput(CPU* cpu){
    SDL_Event e;
    SDL_PollEvent(&e);
   
    if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_1: cpu->Key[0x1] = 1;break;
            case SDLK_2: cpu->Key[0x2] = 1;break;
            case SDLK_3: cpu->Key[0x3] = 1;break;
            case SDLK_4: cpu->Key[0xC] = 1;break;
            case SDLK_q: cpu->Key[0x4] = 1;break;
            case SDLK_w: cpu->Key[0x5] = 1;break;
            case SDLK_e: cpu->Key[0x6] = 1;break;
            case SDLK_r: cpu->Key[0xD] = 1;break;
            case SDLK_a: cpu->Key[0x7] = 1;break;
            case SDLK_s: cpu->Key[0x8] = 1;break;
            case SDLK_d: cpu->Key[0x9] = 1;break;
            case SDLK_f: cpu->Key[0xE] = 1;break;
            case SDLK_z: cpu->Key[0xA] = 1;break;
            case SDLK_x: cpu->Key[0x0] = 1;break;
            case SDLK_c: cpu->Key[0xB] = 1;break;
            case SDLK_v: cpu->Key[0xF] = 1;break;


            default:
                break;
        }
    }

    if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym){
            case SDLK_1: cpu->Key[0x1] = 1; break;
            case SDLK_2: cpu->Key[0x2] = 1; break;
            case SDLK_3: cpu->Key[0x3] = 1; break;
            case SDLK_4: cpu->Key[0xC] = 1; break;
            case SDLK_q: cpu->Key[0x4] = 1; break;
            case SDLK_w: cpu->Key[0x5] = 1; break;
            case SDLK_e: cpu->Key[0x6] = 1; break;
            case SDLK_r: cpu->Key[0xD] = 1; break;
            case SDLK_a: cpu->Key[0x7] = 1; break;
            case SDLK_s: cpu->Key[0x8] = 1; break;
            case SDLK_d: cpu->Key[0x9] = 1; break;
            case SDLK_f: cpu->Key[0xE] = 1; break;
            case SDLK_z: cpu->Key[0xA] = 1; break;
            case SDLK_x: cpu->Key[0x0] = 1; break;
            case SDLK_c: cpu->Key[0xB] = 1; break;
            case SDLK_v: cpu->Key[0xF] = 1; break;

            default:
                break;
        }
    }
}

void C8_waitInput(CPU* cpu){
    SDL_Event e;
    SDL_WaitEvent(&e);
   
    if (e.type == SDL_KEYDOWN){
        switch (e.key.keysym.sym){
            case SDLK_1: cpu->Key[0x1] = 1;break;
            case SDLK_2: cpu->Key[0x2] = 1;break;
            case SDLK_3: cpu->Key[0x3] = 1;break;
            case SDLK_4: cpu->Key[0xC] = 1;break;
            case SDLK_q: cpu->Key[0x4] = 1;break;
            case SDLK_w: cpu->Key[0x5] = 1;break;
            case SDLK_e: cpu->Key[0x6] = 1;break;
            case SDLK_r: cpu->Key[0xD] = 1;break;
            case SDLK_a: cpu->Key[0x7] = 1;break;
            case SDLK_s: cpu->Key[0x8] = 1;break;
            case SDLK_d: cpu->Key[0x9] = 1;break;
            case SDLK_f: cpu->Key[0xE] = 1;break;
            case SDLK_z: cpu->Key[0xA] = 1;break;
            case SDLK_x: cpu->Key[0x0] = 1;break;
            case SDLK_c: cpu->Key[0xB] = 1;break;
            case SDLK_v: cpu->Key[0xF] = 1;break;


            default:
                break;
        }
    }

    if (e.type == SDL_KEYUP){
        switch (e.key.keysym.sym){
            case SDLK_1: cpu->Key[0x1] = 1; break;
            case SDLK_2: cpu->Key[0x2] = 1; break;
            case SDLK_3: cpu->Key[0x3] = 1; break;
            case SDLK_4: cpu->Key[0xC] = 1; break;
            case SDLK_q: cpu->Key[0x4] = 1; break;
            case SDLK_w: cpu->Key[0x5] = 1; break;
            case SDLK_e: cpu->Key[0x6] = 1; break;
            case SDLK_r: cpu->Key[0xD] = 1; break;
            case SDLK_a: cpu->Key[0x7] = 1; break;
            case SDLK_s: cpu->Key[0x8] = 1; break;
            case SDLK_d: cpu->Key[0x9] = 1; break;
            case SDLK_f: cpu->Key[0xE] = 1; break;
            case SDLK_z: cpu->Key[0xA] = 1; break;
            case SDLK_x: cpu->Key[0x0] = 1; break;
            case SDLK_c: cpu->Key[0xB] = 1; break;
            case SDLK_v: cpu->Key[0xF] = 1; break;

            default:
                break;
        }
    }
}