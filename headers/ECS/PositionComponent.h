//
// Created by Jakub Górski on 16/06/2022.
//

#ifndef BATTLESHIPS_GAME_POSITIONCOMPONENT_H
#define BATTLESHIPS_GAME_POSITIONCOMPONENT_H

#include "Components.h"

class PositionComponent : public Component {
private:
    int xpos{}, ypos{};
public:

    PositionComponent() {
        xpos = ypos = 0;
    }

    PositionComponent(int x, int y){
        xpos = x;
        ypos = y;
    }

    void update() override {
        xpos++;
        ypos++;
    }

    void setPos(int x, int y){
        xpos = x;
        ypos = y;
    }

    int x() const { return xpos; }
    int y() const { return ypos; }

};

#endif //BATTLESHIPS_GAME_POSITIONCOMPONENT_H
