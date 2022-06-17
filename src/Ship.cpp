//
// Created by jack on 21/03/2022.
//

#include "Ship.h"
#include "TextureManager.h"

Ships::Ships() {
    Submarine.size = 1;
    Submarine.name = "Submarine";
    Submarine.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::ship1x1) + ".png");

    Destroyer.size = 2;
    Destroyer.name = "Destroyer";
    Destroyer.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");
    Destroyer.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");

    Cruiser.size = 3;
    Cruiser.name = "Cruiser";
    Cruiser.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");
    Cruiser.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Cruiser.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");

    Battleship.size = 4;
    Battleship.name = "Battleship";
    Battleship.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");
    Battleship.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Battleship.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Battleship.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");

    Carrier.size = 5;
    Carrier.name = "Carrier";
    Carrier.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");
    Carrier.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Carrier.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Carrier.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipmid) + ".png");
    Carrier.textures.push_back("../res/textures/tiles/"+ std::to_string(TEX::shipend) + ".png");

    ShipCount[0] = std::make_pair(Submarine, 2);
    ShipCount[1] = std::make_pair(Destroyer, 2);
    ShipCount[2] = std::make_pair(Cruiser, 1);
    ShipCount[3] = std::make_pair(Battleship, 1);
    ShipCount[4] = std::make_pair(Carrier, 1);
}

void Ships::reduceShipCount(int type, int amount) {
    ShipCount[type].second -= amount;
}

std::pair<Ship, int> Ships::getShipType(int type) {
    return ShipCount[type];
}

int Ships::getShipCount(int type) {
    return ShipCount[type].second;
}

int Ships::shipsLeft(){
    int left{};
    for (int i = 0; i < 5; i++){
        left += ShipCount[i].second;
    }
    return left;
}

void Ships::_debug_delete_ships() {
    for(auto & i : ShipCount){
        i.second = 0;
    }
}
