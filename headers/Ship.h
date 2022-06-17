//
// Created by jack on 21/03/2022.
//

#ifndef BATTLESHIPS_GAEM_SHIP_H
#define BATTLESHIPS_GAEM_SHIP_H

#include <utility>
#include <string>
#include <vector>
#include <SDL.h>
#include "TextureManager.h"
#include <iostream>

struct Ship {
    int size;
    std::string name;
    std::vector<std::string> textures;
};

class Ships {
private:
    Ship Submarine;
    Ship Destroyer;
    Ship Cruiser;
    Ship Battleship;
    Ship Carrier;
    std::pair<Ship, int> ShipCount[5];
public:
    Ships();
    void reduceShipCount(int type, int amount);
    std::pair<Ship, int> getShipType(int type);
    int getShipCount(int type);
    int shipsLeft();

    void _debug_delete_ships();
};


#endif //BATTLESHIPS_GAEM_SHIP_H
