#ifndef HANDELINPUT_H_INCLUDED
#define HANDELINPUT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

struct EventPlayer
{
    int x , y ;// tọa độ chuột

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL) ;

    static bool start_game;
    static bool quit_game;
    static bool in_start;
    static bool in_quit;

    static bool event_key_up;
    static bool event_key_down;
    static bool event_key_right;
    static bool event_key_left ;
    static bool event_key_f;
    static bool isFPressed;

    static int cnt_key_f;
    int status = WALK_RIGHT ;

    void HandelInputAction(SDL_Event &event, Graphics_ &graphic , Map &map_ )
    {
        //SU KIEN BAN PHIM
        if(currentKeyStates[SDL_SCANCODE_UP])
        {
            event_key_up = true;
        }
        else event_key_up = false;

        if(currentKeyStates[SDL_SCANCODE_DOWN])
        {
            event_key_down = true;
        }
        else event_key_down = false;

        if(currentKeyStates[SDL_SCANCODE_RIGHT])
        {
                event_key_right = true;
                status = WALK_RIGHT;
        }
        else event_key_right = false;

        if(currentKeyStates[SDL_SCANCODE_LEFT])
        {
            event_key_left = true;
            status = WALK_LEFT;
        }
        else event_key_left = false;

        if (event.type == SDL_KEYDOWN) {
            if(isFPressed)
            {
                event_key_f = false;
            }
            else if (!isFPressed && event.key.keysym.sym == SDLK_f) {
                isFPressed = true;
                event_key_f = true;
            }
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_f) {
                isFPressed = false;
                event_key_f = false;
            }
        }

        //SU KIEN CHUOT
        SDL_GetMouseState(&x , &y);
        if(x > 465 && x < 762 && y > 320 && y<348)
        {
            in_start = true;
        }
        else
        {
            in_start = false;
        }

        if(x > 540 && x <655 && y > 420 && y < 448)
        {
            in_quit = true;
        }
        else
        {
            in_quit = false;
        }

        if(event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(x > 465 && x < 762 && y > 320 && y<348)
            {
                start_game = true;
            }
            else if(x > 540 && x <655 && y > 420 && y < 448)
            {
                quit_game = true;
            }

        }
    }

};

bool EventPlayer::start_game = false;
bool EventPlayer::quit_game = false;
bool EventPlayer::in_start = false;
bool EventPlayer::in_quit = false;

bool EventPlayer::event_key_up = false;
bool EventPlayer::event_key_down = false;
bool EventPlayer::event_key_right = false;
bool EventPlayer::event_key_left = false;
bool EventPlayer::event_key_f = false;
bool EventPlayer::isFPressed = false;
int EventPlayer::cnt_key_f = 0;

#endif // HANDELINPUT_H_INCLUDED
