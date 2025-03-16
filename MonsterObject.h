#ifndef MONSTEROBJECT_H_INCLUDED
#define MONSTEROBJECT_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "defs.h"
#include "graphics.h"
#include "BulletMonster.h"
#include "playerObject.h"


struct MonsterObject : public Base
{
    SDL_Texture *texture;
    std::vector <SDL_Rect> clip;

    int currentFrame =0;

    double x_pos =0 , y_pos = 0;
    int x_monster , y_monster;
    // vị trí các ô nhân vật đứng
    int tile_x1 ,tile_y1;
    int tile_x2 , tile_y2;


    double x_val=0 , y_val=0 ;

    bool on_ground = false;
    bool monster_fire = true;


    int width_monster=0 ;
    int height_monster=0 ;


    int type_monster = MONSTER_MOVE;
    int Monster_status = MONSTER_MOVE_LEFT;

    // khoảng giới hạn di chuyển của quái
    int lim_left=0 , lim_right=0;

    std::vector <BulletMonster*> p_bullet_list;

    bool LoadImg_monster(const char * file, SDL_Renderer* renderer)
    {
        bool res= LoadImg(file , renderer);
        if(res )
        {
            //check_move.width_player = rect.w/8;
            //check_move.height_player = rect.h;
        }
        if(!res)
        {
            std::cerr<< "loadImg_monster fail\n";
        }
        return res;
    }

    void set_x_pos(const double &x ) {x_pos = x;}
    void set_y_pos(const double &y )  {y_pos = y;}
    void set_Monster_type (const int &x ) {type_monster = x;}
    void set_rect_monster(const int &x , const int &y)
    {
        width_monster = x;
        height_monster = y;
    }
    void set_Monster_status (const int &x ) {Monster_status = x;}
    void set_lim_move (const int &x , const int &y)
    {
        lim_right = x;
        lim_left = y;
    }

    void ImpMoveType(Graphics_ graphic)
    {
        if(type_monster == MONSTER_MOVE && p_object != NULL)
        {
            if(on_ground == true)
            {
                if(x_pos > lim_right)
                {
                    Monster_status = MONSTER_MOVE_LEFT ;
                    LoadImg_monster(LEFT_MONSTER2_FILE , graphic.renderer);
                    init(p_object , MONSTER2_FRAME , MONSTER_CLIP2);
                }
                else if(x_pos  < lim_left)
                {
                    Monster_status = MONSTER_MOVE_RIGHT ;
                    LoadImg_monster(RIGHT_MONSTER2_FILE , graphic.renderer);
                    init(p_object , MONSTER2_FRAME , MONSTER_CLIP2);
                }
            }
        }

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
    void show( Map &map_ , Graphics_ &graphic  )
    {
        SetRect(x_pos - map_.start_x , y_pos - map_.start_y );
        render(rect.x , rect.y , graphic.renderer);
        tick();
    }

    void DoMonster(Map &map_ )
    {
        x_val = 0;
        y_val += ACCELERATION;
        if(y_val >= MAX_ACCELERATION) y_val = MAX_ACCELERATION;

        if(type_monster == MONSTER_MOVE)
        {
            if(Monster_status == MONSTER_MOVE_RIGHT)
            {
                x_val += MONSTER_SPEED;
            }
            else
            {
                x_val -= MONSTER_SPEED;
            }
        }
        Check_Move(map_);
        x_monster = x_pos - map_.start_x;
        y_monster = y_pos - map_.start_y;
    }

    void Check_Move(Map &map_)
    {
        // check di chuyển ngang
        int height_min = (height_monster < TILE_SIZE) ? height_monster : TILE_SIZE;

        tile_x1 = (x_pos + x_val) / TILE_SIZE;
        tile_y1 = (y_pos) / TILE_SIZE;
        tile_x2 = (x_pos + x_val + width_monster - 1) / TILE_SIZE;
        tile_y2 = (y_pos + height_min - 1) / TILE_SIZE;

        if(tile_x1 >= 0 && tile_y1 >= 0 && tile_x2 < MAX_MAP_X && tile_y2 < MAX_MAP_Y)
        {
            if(x_val > 0)
            {
                int val1 = map_.tile[tile_y1][tile_x2];
                int val2 = map_.tile[tile_y2][tile_x2];

                if((val1 != 0 && val1 != 4) || (val2 != 0 && val2 != 4))
                {
                    x_pos = tile_x2 * TILE_SIZE - width_monster - 1;
                    x_val = 0;
                }
            }
            else
            {
                int val1 = map_.tile[tile_y1][tile_x1];
                int val2 = map_.tile[tile_y2][tile_x1];

                if((val1 != 0 && val1 != 4) || (val2 != 0 && val2 != 4))
                {
                    x_pos = (tile_x1 + 1) * TILE_SIZE;
                    x_val = 0;
                }
            }
        }

        // check di chuyen doc
        int width_min = (width_monster < TILE_SIZE) ? width_monster : TILE_SIZE;

        tile_x1 = x_pos / TILE_SIZE;
        tile_y1 = (y_pos + y_val) / TILE_SIZE;
        tile_x2 = (x_pos + width_min - 1) / TILE_SIZE;
        tile_y2 = (y_pos + y_val + height_monster - 1) / TILE_SIZE;

        if(tile_x1 >= 0 && tile_y1 >= 0 && tile_x2 < MAX_MAP_X && tile_y2 < MAX_MAP_Y)
        {
            if(y_val > 0)
            {
                int val1 = map_.tile[tile_y2][tile_x1];
                int val2 = map_.tile[tile_y2][tile_x2];

                if((val1 != 0 && val1 != 4) || (val2 != 0 && val2 != 4))
                {
                    y_pos = tile_y2 * TILE_SIZE - height_monster - 1;
                    y_val = 0;
                    on_ground = true;
                }
            }
        }

        x_pos += x_val;
        y_pos += y_val;

        if(x_pos < 0) x_pos = 0;
        else if(x_pos + width_monster > map_.max_x) x_pos = map_.max_x - width_monster;
    }


    void InItBullet (BulletMonster *p_bullet , Graphics_ &graphic)
    {
        if(p_bullet != NULL)
        {
            if(type_monster == MONSTER_MOVE)
            {
                bool res = p_bullet->LoadImg(LAZE , graphic.renderer);
                p_bullet->init_bullet();
                p_bullet->set_x_val(SPEED_BULLET1 );
                p_bullet->set_y_val(SPEED_BULLET1);
                p_bullet->set_x_start(x_monster);
                p_bullet->set_y_start(y_monster + 25);
                p_bullet->SetRect(x_monster , y_monster + 25);
                p_bullet->set_bullet_dir(DIR_LEFT);
                if(res) p_bullet_list.push_back(p_bullet);
            }
            else
            {
                bool res = p_bullet->LoadImg(BULLET_MONSTER_STONE , graphic.renderer);
                p_bullet->init_bullet();
                p_bullet->set_x_val(SPEED_BULLET2);
                p_bullet->set_y_val(SPEED_BULLET2);
                p_bullet->set_x_start(x_monster);
                p_bullet->set_y_start(y_monster + 5);
                p_bullet->SetRect(x_monster , y_monster + 5);
                p_bullet->set_bullet_dir(DIR_NONE);
                if(res) p_bullet_list.push_back(p_bullet);
            }
        }
    }

    void MakeBullet(Map &map_ , Graphics_ &graphic , const int &x_limit , const int &y_limit , const int &x_player , const int &y_player)
    {
        for(int i=0 ; i < p_bullet_list.size() ; i++)
        {
            BulletMonster* p_bullet = p_bullet_list[i];

            if(texture == NULL)
            {
                p_bullet->free();
                p_bullet = NULL;
                p_bullet_list.erase(p_bullet_list.begin() + i);
            }
            if(p_bullet != NULL)
            {
                if(p_bullet->bullet_out == false)
                {

                    //if(Monster_status == MONSTER_MOVE_LEFT ) p_bullet->set_bullet_dir(DIR_LEFT);
                    //else if(Monster_status == MONSTER_MOVE_RIGHT) p_bullet->set_bullet_dir(DIR_RIGHT);
                    p_bullet->Move_Check(map_ , x_limit , y_limit , x_player , y_player);
                    p_bullet->Render(graphic.renderer);
                }
                else
                {
                    p_bullet->set_bullet_out(false);
                    p_bullet->SetRect(x_monster , y_monster + 25);
                    p_bullet->set_x_start(x_monster);
                    p_bullet->set_y_start(y_monster + 25);

                    /*p_bullet->free();
                    p_bullet=NULL;
                    p_bullet_list.erase(p_bullet_list.begin() + i);
                    BulletMonster* p_bullet_new = new BulletMonster();
                    InItBullet(p_bullet_new , graphic);*/
                }
            }
        }
    }

};

#endif // MONSTEROBJECT_H_INCLUDED
