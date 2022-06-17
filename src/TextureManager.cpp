//
// Created by Jakub Górski on 11/06/2022.
//

#include "TextureManager.h"
#include <SDL_image.h>

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface *surface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(GameMaster::renderer, surface);
    if(!texture){
        PLOGE << "TextureManager loading error: " << SDL_GetError();
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, double angle) {
    SDL_RenderCopyEx(GameMaster::renderer, tex, &src, &dest, angle, nullptr, SDL_FLIP_NONE);
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dest, double angle) {
    SDL_RenderCopyEx(GameMaster::renderer, tex, src, dest, angle, nullptr, SDL_FLIP_NONE);
}
