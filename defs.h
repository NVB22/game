#ifndef DEFS_H_INCLUDED
#define DEFS_H_INCLUDED

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

#define RENDER_DRAW_COLOR 0xff
#define COLOR_KEY_R 167
#define COLOR_KEY_G 175
#define COLOR_KEY_B 180
#define WINDOW_TITLE "Hello World!"

#define TILE_SIZE 64
#define MAX_MAP_X 400
#define MAX_MAP_Y 10

const int HEALTH_PLAYER = 5;
int MARK = 0;
int MONEY = 0;

const char* MAP_FILE = "map/map01.dat";
const char* JUMP_RIGHT_SPRITE_FILE = "img/jum_right.png";
const char* JUMP_LEFT_SPRITE_FILE = "img/jum_left.png";
const char* RIGHT1_SPRITE_FILE = "img/player_right.png";
const char* LEFT1_SPRITE_FILE = "img/player_left.png";
const char* BULLET_MONSTER_STONE = "img/bullet_stone.png";

const char* BULLET1 = "img/bullet.png";
const char* BULLET2 = "img/round_bullet_20x20.png";
const char* LAZE = "img/bullet1.png";
const char* EXP = "img/exp3.png";

const char* LEFT_MONSTER1_FILE = "img/threat_level.png";
const char* LEFT_MONSTER2_FILE = "img/threat_left.png";
const char* RIGHT_MONSTER2_FILE = "img/threat_right.png";


const int WIDTH_PLAYER = 60;
const int HEIGHT_PLAYER = 64 ;

//kích thước của quái
const int WIDTH_MONSTER1 = 60;
const int HEIGHT_MONSTER1 = 60;

const int WIDTH_MONSTER2 = 60 ;
const int HEIGHT_MONSTER2 = 50 ;

const int WIDTH_EXP = 150;
const int HEIGHT_EXP = 165;

const int DISTANCE = 200;

const int PLAY1_CLIP1[][4] = {
    {0,0, 60 , 64},
    {60 , 0 , 60 , 64},
    {120 , 0 , 60 , 64},
    {180 , 0 , 60 , 64},
    {240 , 0 , 60 , 64},
    {300 , 0 , 60 , 64},
    {360 , 0 , 60 , 64},
    {420 , 0 , 60 , 64},

};
const int MONSTER_CLIP1[][4] = {
    {0,0, 60 , 60},
    {60 , 0 , 60 , 60},
    {120 , 0 , 60 , 60},
    {180 , 0 , 60 , 60},
    {240 , 0 , 60 , 60},
    {300 , 0 , 60 , 60},
    {360 , 0 , 60 , 60},
    {420 , 0 , 60 , 60},

};
const int MONSTER_CLIP2[][4] = {
    {0,0, 60 , 50},
    {60 , 0 , 60 , 50},
    {120 , 0 , 60 , 50},
    {180 , 0 , 60 , 50},
    {240 , 0 , 60 , 50},
    {300 , 0 , 60 , 50},
    {360 , 0 , 60 , 50},
    {420 , 0 , 60 , 50},
};

const int EXP_CLIP[][4] =
{
    {0 , 0 , 150 , 165 },
    {150 , 0 , 150 , 165},
    {300 , 0 , 150 , 165},
    {450 , 0 , 150 , 165},
    {600 , 0 , 150 , 165},
    {750 , 0 , 150 , 165},
    {900 , 0 , 150 , 165},
    {1050 , 0 , 150 , 165},
    {1200 , 0 , 150 , 165}
};

const int PLAYER1_FRAME = sizeof(PLAY1_CLIP1)/sizeof(int)/4;
const int MONSTER1_FRAME =sizeof(MONSTER_CLIP1)/sizeof(int)/4;
const int MONSTER2_FRAME = sizeof(MONSTER_CLIP2)/sizeof(int)/4;
const int EXP_FRAME = sizeof(EXP_CLIP)/sizeof(int)/4;

const int MONSTER_MOVE = 100 ;
const int MONSTER_NOT_MOVE = 101;


const double ACCELERATION = 0.8 ;
const int MAX_ACCELERATION = 12;
const int INITIAL_SPEED = 10;
//const int GRAVITY_SPEED = 12;

const int MONSTER_SPEED = 3;
const int MONSTER_MOVE_LEFT = 110;
const int MONSTER_MOVE_RIGHT = 111;


const int NOT_WALK = 0;
const int WALK_UP = 1;
const int WALK_RIGHT = 2;
const int WALK_LEFT = 3;

const int NOT = 0;
const int UP = 1;
const int RIGHT = 2;
const int LEFT = 3;

const int DIR_NONE = 29;
const int DIR_RIGHT = 30;
const int DIR_LEFT = 31;
const int DIR_UP_RIGHT = 32;
const int DIR_DOWN_RIGHT = 33;
const int DIR_UP_LEFT = 34;
const int DIR_DOWN_LEFT =35;
const int SPEED_BULLET1 = 30;
const int SPEED_BULLET2 = 10;
//#define BACKGROUND_IMG "img\\forest.jpg"

SDL_Color color_White = {255, 255, 255};
SDL_Color color_Red = {255, 0, 0};

#define BACKGROUND_IMG "img\\123456.png"

#endif // DEFS_H_INCLUDED
