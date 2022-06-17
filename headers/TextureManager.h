//
// Created by Jakub Górski on 11/06/2022.
//

#ifndef BATTLESHIPS_GAME_TEXTUREMANAGER_H
#define BATTLESHIPS_GAME_TEXTUREMANAGER_H

#include "GameMaster.h"

#include <string>
#include <SDL.h>

class TextureManager {
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, double angle = 0);
    static void Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest, double angle = 0);
};

#endif //BATTLESHIPS_GAME_TEXTUREMANAGER_H
