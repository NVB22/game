#ifndef BULLETMONSTER_H_INCLUDED
#define BULLETMONSTER_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"
#include "graphics.h"
#include "gameMap.h"
#include "MonsterObject.h"
#include "playerObject.h"
#include "baseObject.h"

struct BulletMonster: public Base
{
    int x_val , y_val;
    int x_start , y_start;
    int x_target , y_target;

    bool bullet_out;

    int  bullet_dir;

    int lim_left , lim_right;
    bool target;

     void init_bullet()
    {

        x_val = 0 ; y_val = 0;

        bullet_out = false ;

        bullet_dir = DIR_NONE;
    }
    void set_x_val (const int &x) {x_val = x;}
    void set_y_val (const int &y) {y_val = y;}

    void set_x_start (const int &x) {x_start = x;}
    void set_y_start (const int &y) {y_start = y;}

    void set_x_target (const int &x) {x_target = x;}
    void set_y_target (const int &y) {y_target = y;}

    void set_bullet_out (bool x) {bullet_out = x;}
    void set_bullet_dir (const int x) {bullet_dir = x;}
    void set_target (bool x) {target = x ;}

    void Move_Check(Map &map_ , const int &x_limit , const int &y_limit , const int &x_player , const int &y_player , int &health_player )
    {
        int tile_x1 , tile_y1;
        int tile_x2 , tile_y2;

        // CHECK TO MAP
        if(bullet_dir == DIR_LEFT)
        {
            rect.x -= x_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 ) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 ) / TILE_SIZE;

            if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
            {
                if( map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                {
                    bullet_out = true;

                }
                else if(rect.x <0 || rect.x > x_limit - width_monster2 || rect.x + 256 < x_start  )
                {
                    bullet_out = true;
                }
            }

        }
        if(bullet_dir == DIR_RIGHT)
        {
            rect.x += (x_val) ;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 ) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 ) / TILE_SIZE;

             if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
             {
                if( map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                {
                    bullet_out = true;

                }
                else if(rect.x <0 || rect.x > x_limit - width_monster2 || rect.x - 256 > x_start)
                {
                    bullet_out = true;
                }
             }

        }
        if(bullet_dir == DIR_NONE)
        {
            if(target == false)
            {
                set_x_target(x_player + 10);
                set_y_target(y_player + 10);
                set_target(true);
            }

            int u1 = x_target - x_start;
            int u2 = y_target - y_start;

            if(u1 != 0 && u2 != 0 )
            {
                if(x_target - rect.x > 0)
                {
                    rect.x += (x_val);
                    if(rect.x > x_target) rect.x = x_target;
                    rect.y = (1.0*(rect.x - x_start)/u1)*u2 + y_start;

                    tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
                    tile_y1 = rect.y / TILE_SIZE;
                    tile_x2 = (rect.x + map_.start_x + rect.w*2/3 ) / TILE_SIZE;
                    tile_y2 = (rect.y + rect.h*2/3 ) / TILE_SIZE;

                    if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
                    {
                         if(rect.x > x_start + 320 || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                        {
                            bullet_out = true;
                            set_target(false);
                        }
                    }


                }
                else if(x_target - rect.x < 0)
                {
                    rect.x -= (x_val + INITIAL_SPEED);

                    if(rect.x < x_target) rect.x = x_target;
                    rect.y = (1.0*(rect.x - x_start)/u1)*u2 + y_start;

                    tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
                    tile_y1 = rect.y / TILE_SIZE;
                    tile_x2 = (rect.x + map_.start_x + rect.w*2/3 ) / TILE_SIZE;
                    tile_y2 = (rect.y + rect.h*2/3 ) / TILE_SIZE;

                    if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
                    {
                        if(rect.x < x_start - 320 || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                        {
                            bullet_out = true;
                            set_target(false);
                        }
                    }

                }
            }
            if(rect.x <0 || rect.x > x_limit - width_monster2 || rect.x == x_target  )
            {
                bullet_out = true;
                set_target(false);
            }

        }

        //CHECK TO PLAYER

        int x1 = x_player;
        int x2 = x_player + width_player;
        int y1 = y_player;
        int y2 = y_player + height_player;
        if(rect.x + 10 > x1 && rect.x + 10 < x2 && rect.y + 10 > y1 && rect.y + 10 < y2  )
        {
            if(bullet_dir == DIR_NONE)
            {
                set_target(false);
            }
            bullet_out = true;
            health_player--;
        }


    }
};

#endif // BULLETMONSTER_H_INCLUDED
