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
    explicit SpriteComponent(SDL_Texture* tex){
        texture = tex;
    }
    explicit SpriteComponent(const char* path){
        setTexture(path);
    }

    void init() override {

        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->height;
    }

    void update() override {
        if(transparent){
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureAlphaMod(texture, alpha);
        }
        else {
            SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
        }
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        destRect.w = transform->width * transform->scaleX;
        destRect.h = transform->height * transform->scaleY;
    }

    void draw() override {
        if(rotated){
            TextureManager::Draw(texture, srcRect, destRect, rotation);
            return;
        }
        TextureManager::Draw(texture, srcRect, destRect);

    }

    void setTexture(const char* path){
        texture = TextureManager::LoadTexture(path);
    }

    void setAlpha(int _alpha){
        alpha = _alpha;
    }

    void setTransparent(){
        transparent = true;
    }
    void unsetTransparent(){
        transparent = false;
    }

    void rotate(double _angle){
        if(rotation == _angle){
            rotated = false;
            return;
        }
        rotation = _angle;
        rotated = true;
    }

    ~SpriteComponent() override { SDL_DestroyTexture(texture); }

private:
    TransformComponent *transform{};
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};

    bool rotated = false;
    double rotation{};
    bool transparent{};
    int alpha{};
};

#endif //BATTLESHIPS_GAME_SPRITECOMPONENT_H
