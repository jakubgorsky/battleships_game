//
// Created by jack on 21/03/2022.
//

#ifndef BATTLESHIPS_GAEM_SHIP_H
#define BATTLESHIPS_GAEM_SHIP_H

#include <utility>
#include <string>

struct ShipType {
    int size;
    std::string name;
};

class Ships {
private:
    ShipType Submarine;
    ShipType Destroyer;
    ShipType Cruiser;
    ShipType Battleship;
    ShipType Carrier;
    std::pair<ShipType, int> ShipCount[5];
public:
    Ships();
    void reduceShipCount(int type, int amount);
};




#endif //BATTLESHIPS_GAEM_SHIP_H
