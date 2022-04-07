//
// Created by jack on 21/03/2022.
//
#include <iostream>
#include "PlayerBoard.h"
#include "Ship.h"
#include "GUI.h"

// debug only lol
int main() {
    Ships PlayerOneShips;
    PlayerBoard b{PlayerOneShips};
//    b.placeShip(0,0,0,PlayerOneShips.getShipType(1).first);
//    b.placeShip(3, 2, 1, PlayerOneShips.getShipType(3).first);
//    b.placeShip(3, 4, 0, PlayerOneShips.getShipType(4).first);
    GUI g{b, PlayerOneShips};
    g.GUI_HANDLER();
    g.PRINT_BOARD();
    system("clear");
    g.PRINT_BOARD();
}