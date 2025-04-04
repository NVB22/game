#include "InItGame.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graphics_ graphic;
    graphic.initSDL();
    GameResources resources;
    InitGame(graphic, resources);

    PlayerIndex player_index;
    player_index.InIt(graphic);

    GameMap game_map_;
    game_map_.LoadMap(MAP_FILE);
    game_map_.LoadTiles(graphic.renderer);

    Sprite player;
    player.LoadImg(RIGHT1_SPRITE_FILE , graphic.renderer);
    player.init(player.p_object, PLAYER1_FRAME, PLAY1_CLIP1);

    Bullet check_fire;

    std::vector<MonsterObject *> p_Monster_list = MakeMonsterList(graphic);

    Explosion exp ;
    exp.LoadImg_exp(EXP , graphic.renderer);
    exp.init(EXP_FRAME , EXP_CLIP);

    SDL_Event event;
    EventPlayer Event_player;

    ImpTimer impTimer;
    impTimer.init();
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
        RunGameLoop(graphic, resources, game_map_, player ,check_fire , p_Monster_list, Event_player, player_index, exp,impTimer,quit);

        SDL_RenderPresent(graphic.renderer);
        SDL_Delay(50);
    }

    CleanMonster(p_Monster_list);
    CleanUp(resources , player , game_map_ , exp);
    graphic.quit();
    return 0;
}
