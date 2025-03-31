#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "baseObject.h"

struct Explosion : public Base
{
    std::vector<SDL_Rect> clip;
    int currentFrame ;
    bool explode = false;

    bool LoadImg_exp(const char*file , SDL_Renderer* renderer)
    {
        bool res = LoadImg(file , renderer);
        if(!res)
        {
            std::cerr<<"Loadimg_exp fail\n";
        }
        return res;
    }
    void init(const int& frame , const int _clip[][4])
    {
        SDL_Rect _Clip;
        for(int i=0; i < frame ;i++)
        {
            _Clip.x = _clip[i][0] ;
            _Clip.y = _clip[i][1] ;
            _Clip.w = _clip[i][2] ;
            _Clip.h = _clip[i][3] ;
            clip.push_back(_Clip);
        }
    }

    void setFrame(const int frame_)
    {
        currentFrame = frame_;
    }

    const SDL_Rect* getCurrentClip() const
    {
        return &(clip[currentFrame]);
    }

     void render(int x ,int y , SDL_Renderer* renderer)
    {
        const SDL_Rect *clip= getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w , clip->h};
        SDL_RenderCopy(renderer, p_object , clip , &renderQuad);

    }

    void show(SDL_Renderer* renderer )
    {
        render(rect.x, rect.y, renderer);
    }
};

#endif // EXPLOSION_H_INCLUDED
