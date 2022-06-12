//
// Created by Jakub Górski on 11/06/2022.
//

#include "TextureManager.h"
#include <SDL_image.h>

SDL_Texture *TextureManager::LoadTexture(const char *fileName) {
    SDL_Surface *surface = IMG_Load(fileName);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(GameMaster::renderer, surface);
    if(!texture){
        PLOGD << "TextureManager loading error: " << SDL_GetError();
        return nullptr;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest) {
    SDL_RenderCopy(GameMaster::renderer, tex, &src, &dest);
}
