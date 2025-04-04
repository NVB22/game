#ifndef INITGAME_H_INCLUDED
#define INITGAME_H_INCLUDED

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
#include "ImpTimer.h"

using namespace std;

std::vector<MonsterObject *> MakeMonsterList (Graphics_ &graphic )
{

    std::vector<MonsterObject*> Monster_list ;

    MonsterObject* Monster_move = new MonsterObject[35];
    for(int i = 0 ; i< 35 ;i++)
    {
        MonsterObject * p_monster = (Monster_move + i);
        if(p_monster != NULL)
        {
            p_monster->LoadImg_monster(LEFT_MONSTER2_FILE , graphic.renderer);
            p_monster->init( p_monster->p_object , MONSTER2_FRAME ,  MONSTER_CLIP2 );
            p_monster->set_Monster_type(MONSTER_MOVE);
            p_monster->set_rect_monster(WIDTH_MONSTER2 ,HEIGHT_MONSTER2);
            p_monster->set_x_pos(500 + 700*i);
            p_monster->set_y_pos(250);
            int left = p_monster->x_pos - DISTANCE/2;
            int right = p_monster->x_pos + DISTANCE/2;
            p_monster->set_lim_move(right , left);

            BulletMonster* p_bullet = new BulletMonster();
            p_monster->InItBullet(p_bullet , graphic);

            Monster_list.push_back(p_monster);
        }
    }

    MonsterObject* Monster_not_move = new MonsterObject[35];

    for(int i=0 ; i<35 ;i++)
    {
        MonsterObject* p_monster = (Monster_not_move + i);
        if(p_monster != NULL)
        {
            p_monster->LoadImg_monster(LEFT_MONSTER1_FILE , graphic.renderer);
            p_monster->init(p_monster->p_object , MONSTER1_FRAME , MONSTER_CLIP1);
            p_monster->set_Monster_type(MONSTER_NOT_MOVE);
            p_monster->set_rect_monster(WIDTH_MONSTER1 , HEIGHT_MONSTER1);
            p_monster->set_x_pos(630 + 710*i);
            p_monster->set_y_pos(250);

            BulletMonster* p_bullet = new BulletMonster();
            p_monster->InItBullet(p_bullet , graphic);

            Monster_list.push_back(p_monster);
        }
    }

    return Monster_list;
}

struct GameResources {
    TTF_Font* font1;
    TTF_Font* font2;
    TTF_Font* font3;

    Mix_Music* backsound;
    Mix_Music* Action;
    Mix_Chunk* player_fire;
    Mix_Chunk* exp_monster;

    SDL_Texture* BackGround = NULL;
    SDL_Texture* playerTexture = NULL;

    SDL_Texture* TimeText = NULL;
    SDL_Texture* Mark = NULL;
    SDL_Texture* Money = NULL;
    SDL_Texture* Pause = NULL;

    SDL_Texture* StartGame = NULL;
    SDL_Texture* Exit = NULL;

    SDL_Texture* Win = NULL;
    SDL_Texture* Lose = NULL;

    bool play_backsound = false;
    bool win = false;
    bool lose = false;
};

void InitGame(Graphics_& graphic, GameResources& resources) {

    resources.font1 = graphic.loadFont("assets/dlxfont_.ttf", 15);
    resources.font2 = graphic.loadFont("assets/dlxfont_.ttf", 30);
    resources.font3 = graphic.loadFont("assets/dlxfont_.ttf", 35);

    resources.backsound = graphic.loadMusic("assets/backsound.mid");
    resources.Action = graphic.loadMusic("assets/Action.mid");
    resources.player_fire = graphic.loadSound("assets/Fire.wav");
    resources.exp_monster = graphic.loadSound("assets/Explosion+1.wav");

    resources.BackGround = graphic.loadTexture("img/backGround.jpg");
    resources.playerTexture = graphic.loadTexture(RIGHT1_SPRITE_FILE);

    resources.Pause = graphic.loadTexture("img/pause.png");
    string win_ = "You Win!";
    resources.Win = graphic.renderText(win_ , resources.font3 , color_White);
    string lose_ = "You Lose!";
    resources.Lose = graphic.renderText(lose_ , resources.font3 , color_Red);
}

void CleanMonster(std::vector<MonsterObject *> p_Monster_list)
{
    for(int i=0 ; i< (int)p_Monster_list.size() ;i++)
    {
        MonsterObject* p_monster = p_Monster_list.at(i);
        if(p_monster != NULL)
        {
            p_monster->free();
            p_monster = NULL;
        }
    }
    p_Monster_list.clear();
}

void ResetGame(Graphics_ &graphic,
               PlayerIndex &player_index,
               GameMap &game_map_,
               Sprite &player,
               Bullet &check_fire,
               std::vector<MonsterObject *> &p_Monster_list,
               Explosion &exp,
               EventPlayer &Event_player,
               ImpTimer &impTimer)
{
    //reset player
    player.reset();
    player.LoadImg(RIGHT1_SPRITE_FILE , graphic.renderer);
    player.init(player.p_object, PLAYER1_FRAME, PLAY1_CLIP1);
    //reset map
    game_map_.LoadMap(MAP_FILE);
    game_map_.LoadTiles(graphic.renderer);
    //reset index
    MARK = 0;
    MONEY = 0;
    player_index.InIt(graphic);
    //reset Monster
    CleanMonster(p_Monster_list);
    p_Monster_list = MakeMonsterList(graphic);
    //reset Exp
    exp.LoadImg_exp(EXP , graphic.renderer);
    exp.init(EXP_FRAME , EXP_CLIP);
    //reset bullet
    check_fire.init_bullet();
    //reset time
    impTimer.init();
    //reset input
    Event_player.reset();

}
void ShowMainMenu(Graphics_& graphic, EventPlayer& Event_player, GameResources &resources) {
    // Nếu nhạc chưa phát, bắt đầu phát nhạc nền
    if (!resources.play_backsound) {
        graphic.play(graphic.loadMusic("assets/backsound.mid"));
        resources.play_backsound = true;
    }

    // Xử lý trạng thái của "Start Game"
    if (!Event_player.in_start) {
        resources.StartGame = graphic.renderText("Start Game", resources.font2, color_White);
        graphic.renderTexture(resources.StartGame, SCREEN_WIDTH * 0.5 - 175, SCREEN_HEIGHT * 0.5);
    } else {
        resources.StartGame = graphic.renderText("Start Game", resources.font3, color_White);
        graphic.renderTexture(resources.StartGame, SCREEN_WIDTH * 0.5 - 200, SCREEN_HEIGHT * 0.5);
    }

    // Xử lý trạng thái của "Exit"
    if (!Event_player.in_quit) {
        resources.Exit = graphic.renderText("Exit", resources.font2, color_Red);
        graphic.renderTexture(resources.Exit, SCREEN_WIDTH * 0.5 - 100, SCREEN_HEIGHT * 0.5 + 100);
    } else {
        resources.Exit = graphic.renderText("Exit", resources.font3, color_Red);
        graphic.renderTexture(resources.Exit, SCREEN_WIDTH * 0.5 - 110, SCREEN_HEIGHT * 0.5 + 100);
    }
}

void RunGameLoop(Graphics_& graphic, GameResources& resources, GameMap& game_map_,
                 Sprite& player,Bullet &check_fire, std::vector<MonsterObject *>& p_Monster_list,
                 EventPlayer& Event_player, PlayerIndex& player_index,Explosion &exp,ImpTimer &impTimer, bool& quit) {

    if (Mix_PlayingMusic() && resources.play_backsound == true ) {
                Mix_HaltMusic();  // Dừng nhạc đang phát
                resources.play_backsound = false;
            }
    graphic.play(resources.Action);

    SDL_SetRenderDrawColor(graphic.renderer, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B, RENDER_DRAW_COLOR);
    SDL_RenderClear(graphic.renderer);

    if (!Event_player.start_game && !Event_player.quit_game) {
        ShowMainMenu(graphic, Event_player, resources);
    }
     if(Event_player.start_game == true && Event_player.quit_game == false)
     {
        // Chạy game chính
        SDL_RenderCopy(graphic.renderer, resources.BackGround, NULL, NULL);

        impTimer.start();
        if(Event_player.pause_game == true)
        {
            impTimer.pause();
        }
        else {
                impTimer.unpause();
                impTimer.update_real_time();
        }

        player.DoPlayer(game_map_.game_map ,Event_player , player_index.health);
        if(Event_player.event_key_f == true) graphic.play(resources.player_fire);
        check_fire.player_fire( game_map_.game_map , graphic  , player.x_player , player.y_player , Event_player ,p_Monster_list , exp);
        if(exp.explode)
        {
            graphic.play(resources.exp_monster);
            for(int frame = 0 ; frame < EXP_FRAME ; frame++)
            {
                exp.setFrame(frame);
                exp.show(graphic.renderer );
            }
            exp.explode = false;
        }

        player.show( game_map_.game_map , graphic , Event_player );
        game_map_.DrawMap(graphic.renderer);
        player_index.Show(graphic);

        for(int i=0 ; i < (int)p_Monster_list.size() ; i++)
        {
            MonsterObject* p_monster = p_Monster_list.at(i);
            if(p_monster != NULL)
            {
                if(Event_player.pause_game == false)
                {
                    p_monster->ImpMoveType(graphic );
                    p_monster->DoMonster(game_map_.game_map );
                }
                p_monster->MakeBullet(game_map_.game_map ,graphic  , player.x_player , player.y_player ,player_index.health,Event_player );
                p_monster->show(game_map_.game_map , graphic);

            }
        }


        // Kiểm tra thắng/thua
        if (player.finishing) {
            Event_player.quit_game = true;
            resources.win = true;
        }
        if(player_index.health <= 0)
        {
            Event_player.quit_game = true;
            resources.lose = true;
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
        Uint32 time_val = impTimer.real_time / 1000;
        cerr<<time_val<<endl;
        Uint32 time_pos = 300 - time_val;
        if(time_pos <= 0)
        {
            Event_player.quit_game = true;
            resources.lose = true;
        }
        else
        {
            string s = time + to_string(time_pos);
            resources.TimeText = graphic.renderText( s , resources.font1 , color_White);
            graphic.renderTexture(resources.TimeText , SCREEN_WIDTH - 200 , 15);
        }
        //SHOW MARK;
        string mark_ = "Mark: ";
        string mark = mark_ + to_string(MARK);
        resources.Mark = graphic.renderText( mark , resources.font1 , color_White);
        graphic.renderTexture(resources.Mark ,SCREEN_WIDTH*0.5 + 50 , 15 );
        //SHOW MONEY
        string money_ = "Money: ";
        string money = money_ + to_string(MONEY);
        resources.Money = graphic.renderText(money , resources.font1 , color_White);
        graphic.renderTexture(resources.Money ,SCREEN_WIDTH*0.5 - 200 , 15 );
        //SHOW NUT PAUSE
        graphic.renderTexture(resources.Pause , SCREEN_WIDTH - 50 , 10);
    }
    if(Event_player.quit_game == true && quit == false)
    {
        if(player_index.highMark < MARK )
        {
            player_index.highMark = MARK;
            player_index.SaveHighScore("assets/highscore.txt", player_index.highMark);
        }

        std::string hs_text = "High Mark: " + std::to_string(player_index.highMark);
        SDL_Texture* hsTexture = graphic.renderText(hs_text, resources.font1, color_Red);

        string hs_pos = "Mark: " + to_string(MARK);
        SDL_Texture* hs_posTex = graphic.renderText(hs_pos ,resources.font1,color_White  );
        if(resources.lose == true)
        {
            graphic.renderTexture(resources.Lose , SCREEN_WIDTH*0.5 - 150 , SCREEN_HEIGHT*0.5);
            graphic.renderTexture(hsTexture,SCREEN_WIDTH*0.5 + 100 , SCREEN_HEIGHT*0.5 - 100);
            graphic.renderTexture(hs_posTex , SCREEN_WIDTH*0.5 - 200 , SCREEN_HEIGHT*0.5 - 100);
        }
        else if(resources.win == true)
        {
            graphic.renderTexture(resources.Win ,SCREEN_WIDTH*0.5 - 150 , SCREEN_HEIGHT*0.5 );
            graphic.renderTexture(hsTexture,SCREEN_WIDTH*0.5 + 100 , SCREEN_HEIGHT*0.5 - 100);
            graphic.renderTexture(hs_posTex , SCREEN_WIDTH*0.5 - 200 , SCREEN_HEIGHT*0.5 - 100);
        }
        else
        {
            quit = true;
        }

        if(Event_player.Replay_game == true)
        {
            ResetGame(graphic , player_index ,game_map_, player ,check_fire , p_Monster_list , exp , Event_player , impTimer);
        }
    }
}

void CleanUp(GameResources& resources ,Sprite &player ,GameMap &game_map_ , Explosion &exp) {

    player.free();
    exp.free();
    game_map_.tile_mat[20].free();

    TTF_CloseFont(resources.font1);
    TTF_CloseFont(resources.font2);
    TTF_CloseFont(resources.font3);

    if (resources.backsound) Mix_FreeMusic(resources.backsound);
    if (resources.Action) Mix_FreeMusic(resources.Action);
    if (resources.player_fire) Mix_FreeChunk(resources.player_fire);
    if (resources.exp_monster) Mix_FreeChunk(resources.exp_monster);

    if (resources.BackGround) SDL_DestroyTexture(resources.BackGround);
    if (resources.playerTexture) SDL_DestroyTexture(resources.playerTexture);

    if(resources.TimeText != NULL) {SDL_DestroyTexture(resources.TimeText); resources.TimeText = NULL;}
    if(resources.Mark != NULL) {SDL_DestroyTexture(resources.Mark) ; resources.Mark = NULL;}
    if(resources.Money != NULL) {SDL_DestroyTexture(resources.Money); resources.Money = NULL;}
    if(resources.StartGame != NULL) {SDL_DestroyTexture(resources.StartGame); resources.StartGame = NULL;}
    if(resources.Exit != NULL) {SDL_DestroyTexture(resources.Exit); resources.Exit = NULL;}
    if(resources.Lose != NULL) {SDL_DestroyTexture(resources.Lose) ; resources.Lose = NULL;}
    if(resources.Win != NULL) {SDL_DestroyTexture(resources.Win) ; resources.Win = NULL;}
}
#endif // INITGAME_H_INCLUDED
