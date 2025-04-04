#ifndef IMPTIMER_H_INCLUDED
#define IMPTIMER_H_INCLUDED

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "baseObject.h"

struct ImpTimer
{
    int start_tick;
    int pause_tick;
    int sum_pause_tick;
    int real_time ;

    bool is_pause;
    bool is_start;

    void init()
    {
        start_tick = 0;
        pause_tick = 0;
        sum_pause_tick = 0;
        real_time = 0;

        is_pause = false;
        is_start = false;
    }

    void start()
    {
        if(is_start == false)
        {
            is_start = true;
            is_pause = false;
            start_tick = SDL_GetTicks();
        }
    }

    void pause()
    {
        if(is_pause == false)
        {
            is_pause = true;
            //is_start = false;
            pause_tick = SDL_GetTicks();
        }
    }
    void unpause()
    {
        if(is_pause == true)
        {
            is_pause = false;
            //is_start = true;
            sum_pause_tick += SDL_GetTicks() - pause_tick;
        }
    }
    void update_real_time()
    {
        real_time = SDL_GetTicks() - start_tick - sum_pause_tick;
    }
    void stop()
    {
        is_pause = false;
        is_start = false;
    }

};

#endif // IMPTIMER_H_INCLUDED
