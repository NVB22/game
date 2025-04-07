#ifndef PLAYERINDEX_H_INCLUDED
#define PLAYERINDEX_H_INCLUDED

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <fstream>
#include "graphics.h"
#include "defs.h"

struct PlayerIndex : public Base
{
    int health;
    int highMark;
    std::vector<int> pos_list;
    int size_pos_list;

    int LoadHighScore(const std::string& filename) {
        std::ifstream file(filename);
        int highscore = 0;
        if (file.is_open()) {
            file >> highscore;
            file.close();
        }
        return highscore;
    }

    void SaveHighScore(const std::string& filename, int score) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file << score;
            file.close();
        }
    }

    void InIt(Graphics_ &graphics )
    {
        highMark = LoadHighScore("assets/highscore.txt");
        bool res = LoadImg("assets/player_pw.png" , graphics.renderer);
        if(!res) return ;
        health = HEALTH_PLAYER;
        if(pos_list.size() > 0)
        {
            pos_list.clear();
        }
        pos_list.push_back(20);
        pos_list.push_back(60);
        pos_list.push_back(100);
        size_pos_list = pos_list.size();
    }

    void Show(Graphics_ &graphic)
    {
        int n = pos_list.size();
        for(int i=0 ; i<n ;i++)
        {
            rect.x = pos_list.at(i);
            rect.y = 0;
            Render(graphic.renderer);
        }
    }

    void Decrease()
    {
        pos_list.pop_back();
        size_pos_list = pos_list.size();
    }
    void InitCrease()
    {
        int last_pos = pos_list.back();
        pos_list.push_back(last_pos + 40);
        size_pos_list = pos_list.size();
    }

};

#endif // PLAYERINDEX_H_INCLUDED
