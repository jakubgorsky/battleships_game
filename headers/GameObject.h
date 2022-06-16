//
// Created by Jakub Górski on 12/06/2022.
//

#ifndef BATTLESHIPS_GAME_GAMEOBJECT_H
#define BATTLESHIPS_GAME_GAMEOBJECT_H

#include "GameMaster.h"

class GameObject {
public:
    GameObject(const char* textureSheet, int x, int y);
    GameObject(const char* textureSheet, int x, int y, int w, int h);
    ~GameObject() = default;

    void Update();
    void Render();

    void SetStatic(bool setStatic);
private:
    int xpos;
    int ypos;
    bool isStatic = false;
    SDL_Texture* goTexture;
    SDL_Rect srcRect, destRect;
};

#endif //BATTLESHIPS_GAME_GAMEOBJECT_H
