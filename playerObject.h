#ifndef PLAYEROBJECT_H_INCLUDED
#define PLAYEROBJECT_H_INCLUDED

#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "gameMap.h"
#include "BulletObject.h"
#include "baseObject.h"
#include "PlayerIndex.h"
#include "HandelInPut.h"

struct Sprite : public Base
{
    SDL_Texture* texture;
    std::vector <SDL_Rect> clip;
    int currentFrame =0;

    bool finishing = false;

    int x_pos=0 , y_pos=0 ; // vị trí hiện tại của nhân vật, quái so với vị trí map ban đầu
    // vị trí các ô nhân vật đứng
    int tile_x1 ,tile_y1;
    int tile_x2 , tile_y2;

    bool bullet_hit = false;

    int on_ground = 0;
    int speed = INITIAL_SPEED;

    double x_val= 0 , y_val = 0 ;
    int x_player , y_player ; //vị trí thực của nhân vật trên cửa sổ game

    bool LoadImg_player(const char * file, SDL_Renderer* renderer)
    {
        bool res= LoadImg(file , renderer);
        if(res )
        {
            //check_move.width_player = rect.w/8;
            //check_move.height_player = rect.h;
        }
        if(!res)
        {
            std::cerr<< "loadImg_player fail\n";
        }
        return res;
    }
    void init( SDL_Texture* _texture , int frame, const int _clip[][4])
    {
        texture= _texture;
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

    void tick()
    {
        currentFrame = (currentFrame+1) % clip.size() ;
    }

    const SDL_Rect* getCurrentClip() const
    {
        return &(clip[currentFrame]);
    }

     void render(int x ,int y , SDL_Renderer* renderer)
    {
        const SDL_Rect *clip= getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w , clip->h};
        SDL_RenderCopy(renderer, texture , clip , &renderQuad);

    }
    void show( Map &map_ , Graphics_ &graphic ,EventPlayer &event_player  )
    {
        //check_player.DoPlayer(map_ , event_player , event_player);

        if(event_player.status == WALK_RIGHT && on_ground == false  )
        {
            LoadImg_player(JUMP_RIGHT_SPRITE_FILE , graphic.renderer);

            init( p_object,PLAYER1_FRAME,PLAY1_CLIP1 );
        }
        if(event_player.status == WALK_LEFT && on_ground == false   )
        {
            LoadImg_player(JUMP_LEFT_SPRITE_FILE , graphic.renderer );

            init(p_object,PLAYER1_FRAME,PLAY1_CLIP1 );
        }
        if(event_player.status == WALK_RIGHT && on_ground == true )
        {
            LoadImg_player(RIGHT1_SPRITE_FILE , graphic.renderer);
            init( p_object,PLAYER1_FRAME,PLAY1_CLIP1);
        }
        if(event_player.status == WALK_LEFT && on_ground == true)
        {
            LoadImg_player(LEFT1_SPRITE_FILE , graphic.renderer);

            init( p_object,PLAYER1_FRAME,PLAY1_CLIP1);
        }
        //if(check_move.status == NOT_WALK)
        SetRect(x_pos - map_.start_x , y_pos - map_.start_y);
        render(rect.x,rect.y, graphic.renderer);

        if((event_player.event_key_up == true && event_player.event_key_down == false) || event_player.event_key_right == true|| event_player.event_key_left == true)
        {
            tick();
        }
        else currentFrame = 0;
    }

     void DoPlayer( Map &map_ ,EventPlayer &event_player ,int &health_player)
{
    x_val = 0 ;
    y_val += ACCELERATION ;
    if(y_val > MAX_ACCELERATION) y_val = MAX_ACCELERATION;

    if(event_player.event_key_up == true && on_ground == 1 && event_player.event_key_down == false)
    {
        y_val -= 18;
        on_ground = 0;
    }
    if(event_player.event_key_right == true) x_val += INITIAL_SPEED ;
    if(event_player.event_key_left == true) x_val -= INITIAL_SPEED;

    Check_player(map_ , health_player) ;
    CenterEntityOnMap(map_  );
    x_player = x_pos - map_.start_x;
    y_player = y_pos - map_.start_y;
}

void CenterEntityOnMap (Map &map_  )
{
    if(x_pos > SCREEN_WIDTH/3)
    {
        map_.start_x = x_pos - SCREEN_WIDTH/3;
        if(map_.start_x + SCREEN_WIDTH > map_.max_x) map_.start_x = map_.max_x - SCREEN_WIDTH;
    }
    else map_.start_x = 0;
    if(y_pos > SCREEN_HEIGHT/2)
    {
        map_.start_y = y_pos - SCREEN_HEIGHT/2;
        if(map_.start_y + SCREEN_HEIGHT > map_.max_y) map_.start_y = map_.max_y - SCREEN_HEIGHT;
    }
    else map_.start_y = 0;
}

void Check_player( Map &map_  , int &health_player)
{
    //CHECK DI CHUYỂN NGANG;
    int height_min = height_player < TILE_SIZE ? height_player : TILE_SIZE;

    tile_x1 = (x_pos + x_val) / TILE_SIZE;
    tile_y1 = y_pos / TILE_SIZE;

    tile_x2 = (x_pos + x_val + width_player -1) / TILE_SIZE;
    tile_y2 = (y_pos + height_min -1) / TILE_SIZE;

    if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
    {
        if(x_val > 0) // nhân vật di chuyển sang phải
        {
            if(map_.tile[tile_y1][tile_x2] == 4 || map_.tile[tile_y2][tile_x2] == 4)
            {
                map_.tile[tile_y1][tile_x2] = 0;
                map_.tile[tile_y2][tile_x2] = 0;
                MONEY++;
            }
            if(map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x2] != 0)
            {
                x_pos = tile_x2 * TILE_SIZE - width_player - 1;
                x_val = 0;
            }
        }
        else if(x_val < 0) // di chuyển sang trái
        {
            if(map_.tile[tile_y1][tile_x1] == 4 || map_.tile[tile_y2][tile_x1] == 4)
            {
                map_.tile[tile_y1][tile_x1] = 0;
                map_.tile[tile_y2][tile_x1] = 0;
                MONEY++;
            }
            if(map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y2][tile_x1] != 0)
            {
                x_pos = (tile_x1 + 1) * TILE_SIZE;
                x_val = 0;
            }
        }
    }

    // CHECK RƠI
    int width_min = width_player < TILE_SIZE ? width_player : TILE_SIZE;
    tile_x1 = (x_pos) / TILE_SIZE;
    tile_y1 = (y_pos + y_val) / TILE_SIZE;

    tile_x2 = (x_pos + width_min) / TILE_SIZE;
    tile_y2 = (y_pos + height_player + y_val -1) / TILE_SIZE;

    if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
    {
        if(y_val > 0)
        {
            if(map_.tile[tile_y2][tile_x1] == 4 || map_.tile[tile_y2][tile_x2] == 4)
            {
                map_.tile[tile_y2][tile_x1] = 0;
                map_.tile[tile_y2][tile_x2] = 0;
                MONEY++;
            }
            if(map_.tile[tile_y2][tile_x1] != 0 || map_.tile[tile_y2][tile_x2] != 0)
            {
                y_pos = tile_y2 * TILE_SIZE;
                y_pos -= (height_player + 1);
                y_val = 0;
                on_ground = 1;
            }
        }
        else if(y_val < 0)
        {
            if(map_.tile[tile_y1][tile_x1] == 4 || map_.tile[tile_y1][tile_x2] == 4)
            {
                map_.tile[tile_y1][tile_x1] = 0;
                map_.tile[tile_y1][tile_x2] = 0;
                MONEY++;
            }
            if(map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0)
            {
                y_pos = (tile_y1 + 1) * TILE_SIZE;
                y_val = 0;
            }
        }
    }
    x_pos += x_val;
    y_pos += y_val;

    if(x_pos < 0) x_pos = 0;
    else if(x_pos > map_.max_x - width_player)
    {
        x_pos = map_.max_x - width_player;
        finishing = true;
    }

    if(y_pos > map_.max_y)
    {
        x_pos -= width_player;
        y_pos = 0;
        on_ground = 0;
        health_player--;
    }

}


};

#endif // PLAYEROBJECT_H_INCLUDED
