#include "InItGame.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graphics_ graphic;
    GameResources resources;
    InitGame(graphic, resources);

    PlayerIndex player_index;
    player_index.InIt(graphic);
    cerr<<player_index.highMark<<endl;

    GameMap game_map_;
    game_map_.LoadMap("map/map01.dat");
    game_map_.LoadTiles(graphic.renderer);

    Sprite player;
    player.init(resources.playerTexture, PLAYER1_FRAME, PLAY1_CLIP1);

    Bullet check_fire;

    std::vector<MonsterObject *> p_Monster_list = MakeMonsterList(graphic);

    Explosion exp ;
    exp.LoadImg_exp(EXP , graphic.renderer);
    exp.init(EXP_FRAME , EXP_CLIP);

    SDL_Event event;
    EventPlayer Event_player;
    bool quit = false;

    // Main game loop
    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            } else {
                Event_player.HandelInputAction(event, graphic, game_map_.game_map);
            }
        }

        // Xử lý game logic & vẽ màn hình
        RunGameLoop(graphic, resources, game_map_, player ,check_fire , p_Monster_list, Event_player, player_index, exp, quit);

        SDL_RenderPresent(graphic.renderer);
        SDL_Delay(50);
    }

    CleanUp(resources );
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
    player.free();

    exp.free();
    game_map_.tile_mat[20].free();
    graphic.quit();
    return 0;
}
