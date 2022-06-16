//
// Created by Jakub Górski on 16/06/2022.
//

#ifndef BATTLESHIPS_GAME_TRANSFORMCOMPONENT_H
#define BATTLESHIPS_GAME_TRANSFORMCOMPONENT_H

#include "Components.h"
#include "Vector2D.h"

class TransformComponent : public Component {
public:
    Vector2D position;

    TransformComponent() {
        position.x = position.y = 0.0f;
    }

    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    void update() override {
    }

    void setPos(float x, float y){
        position.x = x;
        position.y = y;
    }

};

#endif //BATTLESHIPS_GAME_TRANSFORMCOMPONENT_H
