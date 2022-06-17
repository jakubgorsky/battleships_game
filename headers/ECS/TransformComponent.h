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

    int height = 64, width = 64;
    int scaleX = 1;
    int scaleY = 1;

    TransformComponent() {
        position.x = position.y = 0.0f;
    }

    TransformComponent(float x, float y){
        position.x = x;
        position.y = y;
    }

    TransformComponent(float x, float y, int _w, int _h, int _scalex, int _scaley){
        position.x = x;
        position.y = y;
        height = _h;
        width = _w;
        scaleX = _scalex;
        scaleY = _scaley;
    }

    void update() override {
    }

    void setPos(float x, float y){
        position.x = x;
        position.y = y;
    }

};

#endif //BATTLESHIPS_GAME_TRANSFORMCOMPONENT_H
