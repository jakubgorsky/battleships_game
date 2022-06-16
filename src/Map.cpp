//
// Created by Jakub Górski on 12/06/2022.
//

#include "Map.h"
#include "TextureManager.h"

Map::Map() {
    for(int i = 0; i < 19; i++){
        textures.push_back(TextureManager::LoadTexture(("../res/textures/tiles/"+ std::to_string(i)+".png").c_str()));
    }

    LoadMap(DEF_BG);

    src.x = src.y = 0;
    src.h = src.w = 64;
    dest.x = dest.y = 0;
    dest.w = 64;
    dest.h = 64;
}

Map::~Map() {

}

void Map::LoadMap(int arr[15][25]) {
    for(int r = 0; r < 15; r++){
        for (int c = 0; c < 25; c++){
            map[r][c] = arr[r][c];
        }
    }
}

void Map::DrawMap() {
    int type = -1;

    for(int c = 0; c < 25; c++){
        for (int r = 0; r < 15; r++){
            dest.x = c*64;
            dest.y = r*64;
            type = map[r][c];
            if(type == -1){
                continue;
            }
            TextureManager::Draw(textures[type], src, dest);
        }
    }
}
