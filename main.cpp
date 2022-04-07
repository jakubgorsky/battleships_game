//
// Created by jack on 21/03/2022.
//
#include <iostream>
#include "PlayerBoard.h"
#include "Ship.h"
#include "GUI.h"

// debug only lol
int main() {
    int x, y;
    FieldStatus status;
    x = y = 1;
    status = Missed;
    PlayerBoard b{};
    Ships PlayerOneShips;
    b.setFieldStatus(x, y, status);
    b.setFieldStatus(2, 0, Hit);
    b.placeShip(0,0,0,PlayerOneShips.getShipType(1).first);
    b.placeShip(3, 2, 1, PlayerOneShips.getShipType(3).first);
    b.placeShip(3, 8, 0, PlayerOneShips.getShipType(4).first);
    for (int i = 3; i < 7; i++){
        b.setFieldStatus(5, i, Sunken);
    }
    GUI g;
    g.PRINT_BOARD(b);
}