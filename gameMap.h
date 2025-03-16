#ifndef GAMEMAP_H_INCLUDED
#define GAMEMAP_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "baseObject.h"
#include "defs.h"



struct Map
{
    int start_x, start_y;

    int max_x, max_y;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* fileName;
};


struct GameMap
{
    Map game_map;
    Base tile_mat[20];

    void LoadMap(const char* name)
    {
        FILE* fb = NULL;
        fopen_s(&fb, name , "rb");
        if(fb == NULL)
        {
            return;
        }

        game_map.max_x = 0;
        game_map.max_y = 0;

        for(int i = 0; i < MAX_MAP_Y; i++)
        {
            for(int j = 0; j < MAX_MAP_X; j++)
            {
                fscanf(fb, "%d", &game_map.tile[i][j]);
                int val = game_map.tile[i][j];
                if(val > 0)
                {
                    if(j > game_map.max_x) game_map.max_x = j;
                    if(i > game_map.max_y) game_map.max_y = i;
                }
            }
        }

        game_map.max_x = (game_map.max_x + 1) * TILE_SIZE;
        game_map.max_y = (game_map.max_y + 1) * TILE_SIZE;
        game_map.start_x = 0;
        game_map.start_y = 0;

        // Quản lý bộ nhớ cho fileName
        game_map.fileName = new char[strlen(name) + 1];
        strcpy(game_map.fileName, name);

        fclose(fb);
    }

    void LoadTiles(SDL_Renderer* renderer)
    {
        char file_img[50];
        FILE* fb = NULL;

        for(int i = 0; i < 20; i++)
        {
            sprintf_s(file_img , "map/%d.png", i);
            fopen_s(&fb , file_img, "rb");
            if(fb == NULL)
            {
                continue;
            }
            fclose(fb);

            tile_mat[i].LoadImg(file_img, renderer);
        }
    }

    void DrawMap(SDL_Renderer* renderer)
    {
        int x1 = 0, y1 = 0;
        int x2 = 0, y2 = 0;
        int map_x = 0, map_y = 0;

        map_x = game_map.start_x / TILE_SIZE;
        map_y = game_map.start_y / TILE_SIZE;

        x1 = (game_map.start_x % TILE_SIZE) * -1;
        y1 = (game_map.start_y % TILE_SIZE) * -1;

        x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);
        y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

        for(int i = y1; i < y2; i += TILE_SIZE)
        {
            map_x = game_map.start_x / TILE_SIZE;
            for(int j = x1; j < x2; j += TILE_SIZE)
            {
                int val = game_map.tile[map_y][map_x];
                if(val > 0 && val < 20) // Kiểm tra không vượt quá chỉ số của mảng
                {
                    tile_mat[val].SetRect(j, i);
                    tile_mat[val].Render(renderer);
                }
                map_x++;
            }
            map_y++;
        }
    }
};


#endif // GAMEMAP_H_INCLUDED
