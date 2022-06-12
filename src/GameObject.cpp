//
// Created by Jakub Górski on 12/06/2022.
//

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
    : xpos(x), ypos(y) {
    goTexture = TextureManager::LoadTexture(textureSheet);
    srcRect.h = 64;
    srcRect.w = 64;
}

GameObject::GameObject(const char *textureSheet, int x, int y, int w, int h)
        : xpos(x), ypos(y){
    goTexture = TextureManager::LoadTexture(textureSheet);
    srcRect.h = h;
    srcRect.w = w;
}

void GameObject::Update() {
    if(!isStatic){
        xpos++;
        ypos++;
    }
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = srcRect.h;
    destRect.w = srcRect.w;
}

void GameObject::Render() {
    SDL_RenderCopy(GameMaster::renderer, goTexture, &srcRect, &destRect);
}

void GameObject::SetStatic(bool setStatic) {
    isStatic = setStatic;
}

