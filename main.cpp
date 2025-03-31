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
#include "Explosion.h"
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "InItGame.h"

using namespace std;

int main(int argc, char *argv[])
{
    Graphics_ graphic;
    graphic.initSDL();

    TTF_Font* font1 = graphic.loadFont("assets/dlxfont_.ttf" , 15);
    TTF_Font* font2 = graphic.loadFont("assets/dlxfont_.ttf" , 30);
    TTF_Font* font3 = graphic.loadFont("assets/dlxfont_.ttf" , 35);

    Mix_Music* backsound = graphic.loadMusic("assets/backsound.mid");
    bool play_backsound = false;
    Mix_Music* Action = graphic.loadMusic("assets/Action.mid");
    Mix_Chunk* player_fire = graphic.loadSound("assets/Fire.wav");
    Mix_Chunk* exp_monster = graphic.loadSound("assets/Explosion+1.wav");

    SDL_Color color_White = {255 , 255 , 255} ,
              color_Red = {255 , 0 , 0};

    SDL_Texture* TimeText = NULL;
    SDL_Texture* Mark = NULL;
    SDL_Texture* Money = NULL;
    SDL_Texture* StartGame = NULL;
    SDL_Texture* Exit = NULL;

    SDL_Texture* Win = NULL;
    string win_ = "You Win";
    Win = graphic.renderText(win_ , font3 , color_White);

    SDL_Texture* Lose = NULL;
    string lose_ = "You Lose";
    Lose = graphic.renderText(lose_ , font3 , color_Red);

    bool win = false;
    bool lose = false;

    PlayerIndex player_index;
    player_index.InIt(graphic);

    SDL_Texture* BackGround = graphic.loadTexture("img/backGround.jpg");

    char name[] = "map/map01.dat";

    GameMap game_map_;

    game_map_.LoadMap(name);
    game_map_.LoadTiles(graphic.renderer);

    Sprite player;
    SDL_Texture* playerTexture=graphic.loadTexture(RIGHT1_SPRITE_FILE);
    player.init( playerTexture,PLAYER1_FRAME,PLAY1_CLIP1);

    Bullet check_fire;
    std::vector <MonsterObject *> p_Monster_list = MakeMonsterList(graphic );

    Explosion exp ;
    exp.LoadImg_exp(EXP , graphic.renderer);
    exp.init(EXP_FRAME , EXP_CLIP);

    SDL_Event event;
    EventPlayer Event_player;
    bool quit=false;
    //VÒNG LẶP CHÍNH CỦA GAME
    while(!quit)
    {
        while(SDL_PollEvent( &event) !=0)
        {
            if( event.type == SDL_QUIT)
            {
                quit=true;
            }
            else
            {
                Event_player.HandelInputAction(event, graphic , game_map_.game_map);
            }
        }

        SDL_SetRenderDrawColor(graphic.renderer, COLOR_KEY_R, COLOR_KEY_G ,  COLOR_KEY_B , RENDER_DRAW_COLOR );
        SDL_RenderClear(graphic.renderer);

        if(Event_player.start_game == false && Event_player.quit_game == false)
        {
            graphic.play(backsound);
            play_backsound = true;

            if(Event_player.in_start == false)
            {
                string start_game = "Start Game";
                StartGame = graphic.renderText(start_game , font2 , color_White);
                graphic.renderTexture(StartGame , SCREEN_WIDTH*0.5 - 175 , SCREEN_HEIGHT*0.5);
            }
            else
            {
                string start_game = "Start Game";
                StartGame = graphic.renderText(start_game , font3 , color_White);
                graphic.renderTexture(StartGame , SCREEN_WIDTH*0.5 - 200 , SCREEN_HEIGHT*0.5);
            }

            if(Event_player.in_quit == false)
            {
                string exit_game = "Exit";
                Exit = graphic.renderText(exit_game , font2 , color_Red);
                graphic.renderTexture(Exit , SCREEN_WIDTH*0.5 - 100 , SCREEN_HEIGHT*0.5 + 100);
            }
            else
            {
                string exit_game = "Exit";
                Exit = graphic.renderText(exit_game , font3 , color_Red);
                graphic.renderTexture(Exit , SCREEN_WIDTH*0.5 - 110 , SCREEN_HEIGHT*0.5 + 100);
            }
        }


        if(Event_player.start_game == true && Event_player.quit_game == false)
        {
             if (Mix_PlayingMusic() && play_backsound == true ) {
                Mix_HaltMusic();  // Dừng nhạc đang phát
                play_backsound = false;
            }
            graphic.play(Action);

            SDL_RenderCopy(graphic.renderer , BackGround , NULL , NULL);

            player.DoPlayer(game_map_.game_map ,Event_player , player_index.health);
             if(Event_player.event_key_f == true) graphic.play(player_fire);
            check_fire.player_fire( game_map_.game_map , graphic  , player.x_player , player.y_player , Event_player ,p_Monster_list , exp);
            if(exp.explode)
            {
                graphic.play(exp_monster);
                for(int frame = 0 ; frame < EXP_FRAME ; frame++)
                {
                    exp.setFrame(frame);
                    exp.show(graphic.renderer );
                }
                exp.explode = false;
            }
            player.show( game_map_.game_map , graphic , Event_player );

            //CHECK WIN
            if(player.finishing == true)
            {
                win = true;
                Event_player.quit_game = true;
            }

            game_map_.DrawMap(graphic.renderer);

            player_index.Show(graphic);

            for(int i=0 ; i < p_Monster_list.size() ; i++)
            {
                MonsterObject* p_monster = p_Monster_list.at(i);
                if(p_monster != NULL)
                {
                    p_monster->ImpMoveType(graphic );
                    p_monster->DoMonster(game_map_.game_map );

                    p_monster->MakeBullet(game_map_.game_map ,graphic  , player.x_player , player.y_player ,player_index.health );
                    p_monster->show(game_map_.game_map , graphic);

                }
            }

            if(player_index.health <= 0)
            {
                Event_player.quit_game = true;
                lose = true;
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
                Event_player.quit_game = true;
                lose = true;
            }
            else
            {
                string s = time + to_string(time_pos);
                TimeText = graphic.renderText( s , font1 , color_White);
                graphic.renderTexture(TimeText , SCREEN_WIDTH - 200 , 15);
            }
            //SHOW MARK;
            string mark_ = "Mark: ";
            string mark = mark_ + to_string(MARK);
            Mark = graphic.renderText( mark , font1 , color_White);
            graphic.renderTexture(Mark ,SCREEN_WIDTH*0.5 + 50 , 15 );
            //SHOW MONEY
            string money_ = "Money: ";
            string money = money_ + to_string(MONEY);
            Money = graphic.renderText(money , font1 , color_White);
            graphic.renderTexture(Money ,SCREEN_WIDTH*0.5 - 200 , 15 );
        }

        if(Event_player.quit_game == true && quit == false)
        {
            if(lose == true)
            {
                graphic.renderTexture(Lose , SCREEN_WIDTH*0.5 - 150 , SCREEN_HEIGHT*0.5);
            }
            else if(win == true)
            {
                graphic.renderTexture(Win ,SCREEN_WIDTH*0.5 - 150 , SCREEN_HEIGHT*0.5 );
            }
            else
            {
                quit = true;
            }
        }

        SDL_RenderPresent(graphic.renderer);

        SDL_Delay(50);

    }

    //DỌN DẸP
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
    player.free();

    //check_fire.quit_bullet_player();
    //player.quit_player();
    if(BackGround != NULL) {SDL_DestroyTexture(BackGround) ; BackGround = NULL;}
    if(playerTexture != NULL) {SDL_DestroyTexture(playerTexture) ; playerTexture = NULL;}

    if(TimeText != NULL) {SDL_DestroyTexture(TimeText); TimeText = NULL;}
    if(Mark != NULL) {SDL_DestroyTexture(Mark) ; Mark = NULL;}
    if(Money != NULL) {SDL_DestroyTexture(Money); Money = NULL;}
    if(StartGame != NULL) {SDL_DestroyTexture(StartGame); StartGame = NULL;}
    if(Exit != NULL) {SDL_DestroyTexture(Exit); Exit = NULL;}
    if(Lose != NULL) {SDL_DestroyTexture(Lose) ; Lose = NULL;}
    if(Win != NULL) {SDL_DestroyTexture(Win) ; Win = NULL;}

    TTF_CloseFont( font1 );
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);

    if(backsound != NULL) Mix_FreeMusic(backsound);
    if(Action != NULL) Mix_FreeMusic(Action);
    if(player_fire != NULL) Mix_FreeChunk(player_fire);

    exp.free();
    graphic.quit();
    game_map_.tile_mat[20].free();
    return 0;
}
