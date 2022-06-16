//
// Created by Jakub Górski on 12/06/2022.
//

#ifndef BATTLESHIPS_GAME_MAP_H
#define BATTLESHIPS_GAME_MAP_H

#include "GameMaster.h"
#include "Definitions.h"

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
