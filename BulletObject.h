#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"
#include "baseObject.h"
#include "graphics.h"
#include "playerObject.h"
#include "HandelInPut.h"
#include "MonsterObject.h"

struct Bullet : public Base
{
    Bullet* p_bullet ;
    std::vector <Bullet*> p_bullet_list;

    int x_val , y_val ; //lượng thay đổi tọa độ (x , y) của viên đạn

    bool bullet_out ;
    bool bullet_move;
    int bullet_dir ;

    void init_bullet()
    {

        x_val = 0 ; y_val = 0;

        bullet_out = false ;

        bullet_dir = DIR_NONE;
    }
    void set_x_val (const int &x) {x_val = x;}
    void set_y_val (const int &y) {y_val = y;}

    void set_bullet_out (bool x) {bullet_move = x;}
    void set_bullet_dir (const int x) {bullet_dir = x;}

    void Move_Check (const int &x_max , const int &y_max , Map &map_ , std::vector <MonsterObject* > &p_monster_list)
    {
        int tile_x1 , tile_y1;
        int tile_x2 , tile_y2;


        // MOVE AND CHECK TO MAP
        if(bullet_dir == DIR_RIGHT)
        {
            rect.x += x_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1 ) / TILE_SIZE;

            if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
            {
                if(rect.x > x_max || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                {
                    bullet_out = true;
                }
            }
        }
        else if(bullet_dir == DIR_UP_RIGHT)
        {
            rect.x += x_val;
            rect.y -= y_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1 ) / TILE_SIZE;

             if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
             {
                  if(rect.x >x_max || rect.y < 0 || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0)
                    {
                        bullet_out = true;
                    }
             }

        }
        else if(bullet_dir == DIR_DOWN_RIGHT)
        {
            rect.x += x_val;
            rect.y += y_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1) / TILE_SIZE;

            if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
            {
                if(rect.x > x_max || rect.y > y_max || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0)
                {
                    bullet_out = true;
                }
            }

        }

        else if(bullet_dir == DIR_UP_LEFT)
        {
            rect.x -= x_val;
            rect.y -= y_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1 ) / TILE_SIZE;

            if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
            {
                 if(rect.x < 0 || rect.y <0 || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0)
                {
                    bullet_out = true;
                }
            }

        }
        else if(bullet_dir == DIR_DOWN_LEFT)
        {
            rect.x -= x_val ;
            rect.y += y_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1) / TILE_SIZE;

            if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
           {
                if(rect.x < 0 || rect.y > y_max || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0)
                {
                    bullet_out = true;
                }
           }
        }
        else if(bullet_dir == DIR_LEFT)
        {
            rect.x -= x_val;

            tile_x1 = (rect.x + map_.start_x) / TILE_SIZE;
            tile_y1 = rect.y / TILE_SIZE;
            tile_x2 = (rect.x + map_.start_x + rect.w*2/3 - 1) / TILE_SIZE;
            tile_y2 = (rect.y + rect.h*2/3 - 1) / TILE_SIZE;

             if(tile_x1 >= 0 && tile_x2 < MAX_MAP_X && tile_y1 >= 0 && tile_y2 < MAX_MAP_Y)
             {
                if(rect.x < 0 || map_.tile[tile_y1][tile_x1] != 0 || map_.tile[tile_y1][tile_x2] != 0 || map_.tile[tile_y2][tile_x1] !=0 || map_.tile[tile_y2][tile_x2] !=0 )
                {
                    bullet_out = true;
                }
             }

        }

        //MOVE ANHD CHECK TO MONSTER
        for(int i=0 ; i<p_monster_list.size() ; i++)
        {
            MonsterObject* p_monster = p_monster_list.at(i);
            if(p_monster != NULL )
            {
                int x1 = p_monster->x_monster;
                int y1 = p_monster->y_monster;
                int x2 = x1 + p_monster->width_monster;
                int y2 = y1 + p_monster->height_monster;

                if(rect.x > x1 && rect.x < x2 && rect.y > y1 && rect.y <y2 )
                {
                    SDL_DestroyTexture(p_monster->texture);
                    p_monster->texture = NULL;
                    p_monster->x_pos = 0;
                    p_monster->y_pos = 0;
                    p_monster->x_monster = 0;
                    p_monster->y_monster = 0;
                    p_monster->free();

                    p_monster_list.erase(p_monster_list.begin() + i);

                     bullet_out = true;
                     MARK++;

                }
            }
        }

    }

    void player_fire( Map &map_ , Graphics_ &graphic  ,const int &x_player , const int &y_player , EventPlayer &event_player ,std::vector <MonsterObject* > p_monster_list)
    {
        p_bullet = new Bullet();
        if(event_player.event_key_f  )
        {
            event_player.event_key_f = false;
            //p_bullet = new Bullet();
            bool res = p_bullet->LoadImg(BULLET1, graphic.renderer);
            p_bullet->set_x_val(SPEED_BULLET1);
            p_bullet->set_y_val(SPEED_BULLET1);
            p_bullet->set_bullet_out(false);

            if(event_player.status == WALK_RIGHT && event_player.event_key_up && event_player.event_key_down == true)
            {
                p_bullet->SetRect(x_player +width_player -20 ,y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_UP_RIGHT);
            }
            else if(event_player.status == WALK_RIGHT && event_player.event_key_down)
            {
                p_bullet->SetRect(x_player + width_player -20 ,y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_DOWN_RIGHT);
            }
            else if(event_player.status == WALK_RIGHT )
            {
                p_bullet->SetRect(x_player + width_player -20 ,y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_RIGHT);
            }


            if(event_player.status == WALK_LEFT && event_player.event_key_up && event_player.event_key_down == true )
            {
                p_bullet->SetRect(x_player,  y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_UP_LEFT);
            }
            else if(event_player.status == WALK_LEFT && event_player.event_key_down)
            {
                p_bullet->SetRect(x_player,  y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_DOWN_LEFT);
            }
            else if(event_player.status == WALK_LEFT )
            {
                p_bullet->SetRect(x_player,  y_player + 64*0.25 );
                p_bullet->set_bullet_dir(DIR_LEFT);
            }

            if(res)
            {
                p_bullet_list.push_back(p_bullet);
            }

        }
        for(int i=0 ;i < p_bullet_list.size()  ; i++)
            {
                Bullet *bullet = p_bullet_list[i];
                if(bullet != NULL)
                    if(bullet->bullet_out == false )
                    {
                        bullet->Move_Check(SCREEN_WIDTH , SCREEN_HEIGHT , map_ ,p_monster_list);
                        bullet->Render(graphic.renderer);
                    }
                    else if(bullet->bullet_out == true)
                    {
                        bullet->free();
                        p_bullet_list.erase(p_bullet_list.begin()+i);
                        delete bullet ;
                        bullet = NULL;
                    }
            }
    }


};


#endif // BULLETOBJECT_H_INCLUDED
