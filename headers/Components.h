//
// Created by Jakub Górski on 14/06/2022.
//

#ifndef BATTLESHIPS_GAME_COMPONENTS_H
#define BATTLESHIPS_GAME_COMPONENTS_H

#include "ECS.h"

class PositionComponent : public Component {
private:
    int xpos{}, ypos{};
public:

    void init() override {
        xpos = 0;
        ypos = 0;
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

#endif //BATTLESHIPS_GAME_COMPONENTS_H
