//
// Created by jack on 21/03/2022.
//

#include <stdexcept>
#include "PlayerBoard.h"

FieldStatus PlayerBoard::getFieldStatus(int x, int y) {
    return Board[x][y];
}

void PlayerBoard::setFieldStatus(int x, int y, FieldStatus status) {
    Board[x][y] = status;
}

void PlayerBoard::placeShip(int x, int y, int rotation, const ShipType& shipType) {
    if (x + shipType.size > BOARD_SIZE || y + shipType.size > BOARD_SIZE) {
        throw std::out_of_range("[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: SHIP LANDS OUTSIDE BOARD");
    }
    if (canPlace(x, y, rotation, shipType)){
        for (int i = 0; i < shipType.size; i++){
            setFieldStatus(x+i, y, Occupied);
        }
    }
    else{
        throw std::invalid_argument("[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: ONE OF THE FIELDS IS OCCUPIED.");
    }
}

FieldStatus PlayerBoard::shootField(int x, int y) {
    if(getFieldStatus(x, y) == Occupied){
        return Hit;
    }
    else if (getFieldStatus(x, y) == Free){
        return Missed;
    }
    else if (getFieldStatus(x, y) == Missed || getFieldStatus(x, y) == Hit){
        return Unavailable;
    }
    else {
        return Default;
    }
}

void PlayerBoard::INITIALIZE_BOARD() {
    for (auto & i : Board){
        for (auto & j : i){
            j = Free;
        }
    }
}

bool PlayerBoard::canPlace(int x, int y, int rotation, const ShipType &shipType) {
    if (rotation%2 == 0){
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x+i, y) == Occupied){
                return false;
            }
        }
    }
    else{
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x, y+i) == Occupied){
                return false;
            }
        }
    }
    return true;
}
