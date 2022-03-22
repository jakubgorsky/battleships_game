//
// Created by jack on 21/03/2022.
//

#include "PlayerBoard.h"

FieldStatus PlayerBoard::getFieldStatus(int x, int y) {
    return Board[x][y];
}

void PlayerBoard::setFieldStatus(int x, int y, FieldStatus status) {
    Board[x][y] = status;
}

void PlayerBoard::placeShip(int x, int y, int rotation, const ShipType& shipType) {
    if (x + shipType.size > BOARD_SIZE || y + shipType.size > BOARD_SIZE) {
        return;
    }
    if (rotation%2 == 0){
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x+i, y) == Occupied){
                return;
            }
            setFieldStatus(x+i, y, Occupied);
        }
    }
    else{
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x, y+i) == Occupied){
                return;
            }
            setFieldStatus(x, y+i, Occupied);
        }
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
