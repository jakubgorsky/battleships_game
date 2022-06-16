//
// Created by Jakub Górski on 16/06/2022.
//

#ifndef BATTLESHIPS_GAME_SPRITECOMPONENT_H
#define BATTLESHIPS_GAME_SPRITECOMPONENT_H

#include "Components.h"
#include "TextureManager.h"
#include <SDL.h>

class SpriteComponent : public Component {
public:
    SpriteComponent() = default;
    explicit SpriteComponent(const char* path){
        setTexture(path);
    }

    void init() override {

        position = &entity->getComponent<PositionComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = srcRect.h = 64;
        destRect.w = destRect.h = 64;
    }

    void update() override {
        destRect.x = position->x();
        destRect.y = position->y();
    }

    void draw() override {
        TextureManager::Draw(texture, srcRect, destRect);
    }

    void setTexture(const char* path){
        texture = TextureManager::LoadTexture(path);
    }

private:
    PositionComponent *position;
    SDL_Texture *texture;

    SDL_Rect srcRect{}, destRect{};
};

#endif //BATTLESHIPS_GAME_SPRITECOMPONENT_H
