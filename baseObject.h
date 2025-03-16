#ifndef BASEOBJECT_H_INCLUDED
#define BASEOBJECT_H_INCLUDED

#include "defs.h"
#include <SDL.h>
#include <SDL_image.h>

struct Base
{
    SDL_Texture *p_object = NULL;
    SDL_Rect rect;
    void initBase()
    {
        p_object=NULL;
        rect.x=0;
        rect.y=0;
        rect.w=0;
        rect.h=0;
    }

    void SetRect(const int& x,const int& y)
    {
        rect.x=x;
        rect.y=y;
    }
    SDL_Rect GetRect() const{return rect;}
    SDL_Texture *GetObject() const {return p_object;}

    bool LoadImg(const char*file,SDL_Renderer* renderer)
    {
        free();
        SDL_Texture *new_texture = NULL;
        SDL_Surface *load_surface = IMG_Load(file);
        if(load_surface != NULL)
        {
            SDL_SetColorKey(load_surface, SDL_TRUE, SDL_MapRGB(load_surface->format,COLOR_KEY_R,COLOR_KEY_G,COLOR_KEY_B));
            new_texture =SDL_CreateTextureFromSurface(renderer,load_surface);
            if(new_texture != NULL)
            {
                rect.w= load_surface->w;
                rect.h= load_surface->h;
            }
            SDL_FreeSurface(load_surface);

        }
        p_object=new_texture;
        return (p_object != NULL);
    }
    void Render(SDL_Renderer* des,const SDL_Rect* clip=NULL)
    {
        SDL_Rect dest={rect.x,rect.y,rect.w,rect.h};
        SDL_RenderCopy(des,p_object,clip,&dest);
    }
    void free()
    {
        if(p_object != NULL)
        {
            SDL_DestroyTexture(p_object);
            p_object= NULL;
            rect.w=0;
            rect.h=0;
        }
    }
};

#endif // BASEOBJECT_H_INCLUDED
