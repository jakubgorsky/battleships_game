//
// Created by Jakub Górski on 16/06/2022.
//

#ifndef BATTLESHIPS_GAME_TILECOMPONENT_H
#define BATTLESHIPS_GAME_TILECOMPONENT_H

#include "ECS/ECS.h"
#include "Components.h"
#include <SDL.h>
#include <string>

class TileComponent : public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    std::string path;

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int id){
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        path = "../res/textures/tiles/" + std::to_string(id) + ".png";
    }

    void init() override {
        entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path.c_str());
        sprite = &entity->getComponent<SpriteComponent>();

    }
};

#endif //BATTLESHIPS_GAME_TILECOMPONENT_H
