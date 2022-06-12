//
// Created by Jakub Górski on 12/06/2022.
//

#ifndef BATTLESHIPS_GAME_MAP_H
#define BATTLESHIPS_GAME_MAP_H

#include "GameMaster.h"

enum TEX {
    water = 0,
    gridtl = 1,
    gridt = 2,
    gridtr = 3,
    gridml = 4,
    gridm = 5,
    gridmr = 6,
    gridbl = 7,
    gridb = 8,
    gridbr = 9,
    sand = 10,
    sandtl = 11,
    sandt = 12,
    sandtr = 13,
    sandml = 14,
    sandmr = 15,
    sandbl = 16,
    sandb = 17,
    sandbr = 18
};

class Map {
public:

    Map();
    ~Map();

    void LoadMap(int arr[15][25]);
    void DrawMap();

private:

    SDL_Rect src, dest;
    std::vector<SDL_Texture*> textures;

    int map[15][25];
};

#endif //BATTLESHIPS_GAME_MAP_H
