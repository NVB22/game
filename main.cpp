#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <string>
#include "graphics.h"
#include "defs.h"
#include "baseObject.h"
#include "gameMap.h"
#include "playerObject.h"
#include "BulletObject.h"
#include "BulletMonster.h"
#include "HandelInPut.h"
#include "PlayerIndex.h"
#include <SDL_ttf.h>


using namespace std;



vector<MonsterObject *> MakeMonsterList (Graphics_ &graphic )
    {

        vector<MonsterObject*> Monster_list ;

        MonsterObject* Monster_move = new MonsterObject[20];
        for(int i = 0 ; i< 20 ;i++)
        {
            MonsterObject * p_monster = (Monster_move + i);
            if(p_monster != NULL)
            {
                p_monster->LoadImg_monster(LEFT_MONSTER2_FILE , graphic.renderer);
                p_monster->init( p_monster->p_object , MONSTER2_FRAME ,  MONSTER_CLIP2 );
                p_monster->set_Monster_type(MONSTER_MOVE);
                p_monster->set_rect_monster(60 ,50);
                p_monster->set_x_pos(700 + 1200*i);
                p_monster->set_y_pos(250);
                int left = p_monster->x_pos - 60;
                int right = p_monster->x_pos + 60;
                p_monster->set_lim_move(right , left);

                BulletMonster* p_bullet = new BulletMonster();
                p_monster->InItBullet(p_bullet , graphic);

                Monster_list.push_back(p_monster);
            }
        }

        MonsterObject* Monster_not_move = new MonsterObject[20];

        for(int i=0 ; i<20 ;i++)
        {
            MonsterObject* p_monster = (Monster_not_move + i);
            if(p_monster != NULL)
            {
                p_monster->LoadImg_monster(LEFT_MONSTER1_FILE , graphic.renderer);
                p_monster->init(p_monster->p_object , MONSTER1_FRAME , MONSTER_CLIP1);
                p_monster->set_Monster_type(MONSTER_NOT_MOVE);
                p_monster->set_rect_monster(60 , 60);
                p_monster->set_x_pos(500 + 1200*i);
                p_monster->set_y_pos(250);

                BulletMonster* p_bullet = new BulletMonster();
                p_monster->InItBullet(p_bullet , graphic);

                Monster_list.push_back(p_monster);
            }
        }
        return Monster_list;
    }

int main(int argc, char *argv[])
{
    Graphics_ graphic;
    graphic.initSDL();

    TTF_Font* font = graphic.loadFont("assets/dlxfont_.ttf" , 15);
    SDL_Color color_White = {255 , 255 , 255} ,
              color_Red = {255 , 0 , 0},
              color_Black = {0 , 0 , 0};

    SDL_Texture* TimeText;
    SDL_Texture* Mark;
    SDL_Texture* Money;

    PlayerIndex player_index;
    player_index.InIt(graphic);

    /*Base background;
    bool res=background.LoadImg("img//background.png",graphic.renderer);

    if(!res) return -1;*/

    char* name="map/map01.dat";

    GameMap game_map_;

    game_map_.LoadMap(name);
    game_map_.LoadTiles(graphic.renderer);


    SDL_Event event;
    EventPlayer Event_player;
   // Base player1Texture;

    Sprite player;
    SDL_Texture* playerTexture=graphic.loadTexture(RIGHT1_SPRITE_FILE);
    player.init( playerTexture,PLAYER1_FRAME,PLAY1_CLIP1);

    //CheckPlayer check_player;

    Bullet check_fire;
    //MonsterObject Monster_object ;
    std::vector <MonsterObject *> p_Monster_list = MakeMonsterList(graphic );

    //CheckMonster check_monster;


    bool quit=false;
    while(!quit)
    {
        while(SDL_PollEvent( &event) !=0)
        {
            if( event.type == SDL_QUIT)
            {
                quit=true;
            }
            Event_player.HandelInputAction(event, graphic , game_map_.game_map);
        }

        SDL_SetRenderDrawColor(graphic.renderer, COLOR_KEY_R, COLOR_KEY_G ,  COLOR_KEY_B , RENDER_DRAW_COLOR );
        SDL_RenderClear(graphic.renderer);

        //background.Render(graphic.renderer,NULL);
        //game_map_.DrawMap(graphic.renderer);

        player.DoPlayer(game_map_.game_map ,Event_player);
        check_fire.player_fire( game_map_.game_map , graphic  , player.x_player , player.y_player , Event_player ,p_Monster_list );
        player.show( game_map_.game_map , graphic , Event_player );

        game_map_.DrawMap(graphic.renderer);

        player_index.Show(graphic);

        for(int i=0 ; i < p_Monster_list.size() ; i++)
        {
            MonsterObject* p_monster = p_Monster_list.at(i);
            if(p_monster != NULL)
            {
                p_monster->ImpMoveType(graphic);
                p_monster->DoMonster(game_map_.game_map );

                p_monster->MakeBullet(game_map_.game_map ,graphic , SCREEN_WIDTH , SCREEN_HEIGHT , player.x_player , player.y_player ,player_index.health );
                p_monster->show(game_map_.game_map , graphic);

            }
        }

        if(player_index.health <= 0)
        {
            player.free();
            quit=true;
        }
        else
        {
            if(player_index.health > 0 && player_index.size_pos_list > player_index.health )
            {
                player_index.Decrease();
            }
            else if(player_index.health > 0 && player_index.size_pos_list < player_index.health)
            {
                player_index.InitCrease();
            }
        }

        // SHOW GAME_TIME
        string time ="Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 time_pos = 300 - time_val;
        if(time_pos <= 0)
        {
            quit=true;
            player.free();
        }
        else
        {
            string s = time + to_string(time_pos);
            TimeText = graphic.renderText( s , font , color_White);
            graphic.renderTexture(TimeText , SCREEN_WIDTH - 200 , 15);
        }
        //SHOW MARK;
        string mark_ = "Mark: ";
        string mark = mark_ + to_string(MARK);
        Mark = graphic.renderText( mark , font , color_White);
        graphic.renderTexture(Mark ,SCREEN_WIDTH*0.5 + 50 , 15 );
        //SHOW MONEY
        string money_ = "Money: ";
        string money = money_ + to_string(MONEY);
        Money = graphic.renderText(money , font , color_White);
        graphic.renderTexture(Money ,SCREEN_WIDTH*0.5 - 200 , 15 );

        SDL_RenderPresent(graphic.renderer);

        SDL_Delay(50);

    }

    for(int i=0 ; i<p_Monster_list.size() ;i++)
    {
        MonsterObject* p_monster = p_Monster_list.at(i);
        if(p_monster != NULL)
        {
            p_monster->free();
            p_monster = NULL;
        }
    }

    p_Monster_list.clear();

    //check_fire.quit_bullet_player();
    //player.quit_player();

    SDL_DestroyTexture(TimeText);
    TTF_CloseFont( font );

    graphic.quit();
    game_map_.tile_mat[20].free();
    return 0;
}
