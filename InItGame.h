#ifndef INITGAME_H_INCLUDED
#define INITGAME_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "graphics.h"
#include "defs.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>

std::vector<MonsterObject *> MakeMonsterList (Graphics_ &graphic )
{

    std::vector<MonsterObject*> Monster_list ;

    MonsterObject* Monster_move = new MonsterObject[40];
    for(int i = 0 ; i< 40 ;i++)
    {
        MonsterObject * p_monster = (Monster_move + i);
        if(p_monster != NULL)
        {
            p_monster->LoadImg_monster(LEFT_MONSTER2_FILE , graphic.renderer);
            p_monster->init( p_monster->p_object , MONSTER2_FRAME ,  MONSTER_CLIP2 );
            p_monster->set_Monster_type(MONSTER_MOVE);
            p_monster->set_rect_monster(WIDTH_MONSTER2 ,HEIGHT_MONSTER2);
            p_monster->set_x_pos(500 + 800*i);
            p_monster->set_y_pos(250);
            int left = p_monster->x_pos - DISTANCE/2;
            int right = p_monster->x_pos + DISTANCE/2;
            p_monster->set_lim_move(right , left);

            BulletMonster* p_bullet = new BulletMonster();
            p_monster->InItBullet(p_bullet , graphic);

            Monster_list.push_back(p_monster);
        }
    }

    MonsterObject* Monster_not_move = new MonsterObject[40];

    for(int i=0 ; i<40 ;i++)
    {
        MonsterObject* p_monster = (Monster_not_move + i);
        if(p_monster != NULL)
        {
            p_monster->LoadImg_monster(LEFT_MONSTER1_FILE , graphic.renderer);
            p_monster->init(p_monster->p_object , MONSTER1_FRAME , MONSTER_CLIP1);
            p_monster->set_Monster_type(MONSTER_NOT_MOVE);
            p_monster->set_rect_monster(WIDTH_MONSTER1 , HEIGHT_MONSTER1);
            p_monster->set_x_pos(630 + 800*i);
            p_monster->set_y_pos(250);

            BulletMonster* p_bullet = new BulletMonster();
            p_monster->InItBullet(p_bullet , graphic);

            Monster_list.push_back(p_monster);
        }
    }

    return Monster_list;
}

#endif // INITGAME_H_INCLUDED
