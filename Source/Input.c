#include "Input.h"
#include <SDL2/SDL.h>

void C8_getInput(CPU* cpu){
    SDL_Event e;
    
    while(SDL_PollEvent(&e)){
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
                case SDLK_ESCAPE: cpu->close = 1;break;

                default:
                    break;
            }
        }
        else if (e.type == SDL_KEYUP){
            switch (e.key.keysym.sym){
                case SDLK_1: cpu->Key[0x1] = 0; break;
                case SDLK_2: cpu->Key[0x2] = 0; break;
                case SDLK_3: cpu->Key[0x3] = 0; break;
                case SDLK_4: cpu->Key[0xC] = 0; break;
                case SDLK_q: cpu->Key[0x4] = 0; break;
                case SDLK_w: cpu->Key[0x5] = 0; break;
                case SDLK_e: cpu->Key[0x6] = 0; break;
                case SDLK_r: cpu->Key[0xD] = 0; break;
                case SDLK_a: cpu->Key[0x7] = 0; break;
                case SDLK_s: cpu->Key[0x8] = 0; break;
                case SDLK_d: cpu->Key[0x9] = 0; break;
                case SDLK_f: cpu->Key[0xE] = 0; break;
                case SDLK_z: cpu->Key[0xA] = 0; break;
                case SDLK_x: cpu->Key[0x0] = 0; break;
                case SDLK_c: cpu->Key[0xB] = 0; break;
                case SDLK_v: cpu->Key[0xF] = 0; break;

                default:
                    break;
            }

        
        }
    }
}

void C8_waitInput(CPU* cpu){
    SDL_Event e;
    SDL_WaitEvent(&e);
    
    for(int i = 0; i < 0x10; i++){
       cpu->Key[i] = i; 
    }

    cpu->close = 0;

    if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP){
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
            case SDLK_ESCAPE: cpu->close = 1;break;

            default:
                break;
        }
    }
}
