//
// Created by jack on 21/03/2022.
//

#include "Ship.h"

Ships::Ships() {
    Submarine.size = 1;
    Submarine.name = "Submarine";
    Destroyer.size = 2;
    Destroyer.name = "Destroyer";
    Cruiser.size = 3;
    Cruiser.name = "Cruiser";
    Battleship.size = 4;
    Battleship.name = "Battleship";
    Carrier.size = 5;
    Carrier.name = "Carrier";
    ShipCount[0] = std::make_pair(Submarine, 2);
    ShipCount[1] = std::make_pair(Destroyer, 2);
    ShipCount[2] = std::make_pair(Cruiser, 1);
    ShipCount[3] = std::make_pair(Battleship, 1);
    ShipCount[4] = std::make_pair(Carrier, 1);
}

void Ships::reduceShipCount(int type, int amount) {
    ShipCount[type].second -= amount;
}

std::pair<ShipType, int> Ships::getShipType(int type) {
    return ShipCount[type];
}

int Ships::getShipCount(int type) {
    return ShipCount[type].second;
}
