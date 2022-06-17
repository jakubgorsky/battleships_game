//
// Created by jack on 21/03/2022.
//

#include <plog/Log.h>
#include "PlayerBoard.h"

FieldStatus PlayerBoard::getFieldStatus(int x, int y) {
    return Board[x][y];
}

void PlayerBoard::setFieldStatus(int x, int y, FieldStatus status) {
    Board[x][y] = status;
}

bool PlayerBoard::placeShip(int x, int y, int rotation, const Ship& shipType) {

    if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE) {
        PLOGE << "[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: SHIP LANDS OUTSIDE BOARD";
        return false;
    }
    if (playerShips.getShipCount(shipType.size - 1) <= 0) {
        PLOGE << "[ERROR] Can't place selected ship type. Reason: NOT ENOUGH SHIPS.";
        return false;
    }
    if (canPlace(x, y, rotation, shipType)){
        if(!rotation%2){
            for (int i = 0; i < shipType.size; i++){
                setFieldStatus(x+i, y, Occupied);
            }
        }
        else {
            for (int i = 0; i < shipType.size; i++){
                setFieldStatus(x, y+i, Occupied);
            }
        }
        playerShips.reduceShipCount(shipType.size - 1, 1);
        return true;
    }
    else{
        return false;
    }
}

FieldStatus PlayerBoard::shootField(int x, int y) {
    if(getFieldStatus(x, y) == Occupied){
        PLOGI << "field ( " << x << ", " << y << ") occupied";
        return Hit;
    }
    else if (getFieldStatus(x, y) == Free){
        PLOGI << "field ( " << x << ", " << y << ") empty, missed.";
        return Missed;
    }
    else if (getFieldStatus(x, y) == Missed || getFieldStatus(x, y) == Hit){
        PLOGI << "field ( " << x << ", " << y << ") unavailable";
        return Unavailable;
    }
    else {
        PLOGI << "something went wrong";
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

bool PlayerBoard::canPlace(int x, int y, int rotation, const Ship &shipType) {
    if (!rotation%2){
        if( x + shipType.size > BOARD_SIZE ) {
            PLOGE << "[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: SHIP LANDS OUTSIDE BOARD";
            return false;
        }
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x+i, y) == Occupied){
                PLOGE << "[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: ONE OF THE FIELDS IS OCCUPIED.";
                return false;
            }
        }
    }
    else{
        if( y + shipType.size > BOARD_SIZE ) {
            PLOGE << "[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: SHIP LANDS OUTSIDE BOARD";
            return false;
        }
        for (int i = 0; i < shipType.size; i++){
            if(getFieldStatus(x, y+i) == Occupied){
                PLOGE << "[ERROR] Can't place the ship on coordinates (" + std::to_string(x) + ";" + std::to_string(y) + ") with rotation " + std::to_string(rotation) + ".\n Reason: ONE OF THE FIELDS IS OCCUPIED.";
                return false;
            }
        }
    }
    return true;
}

//PlayerBoard PlayerBoard::autoPlace(PlayerBoard& board, int index) {
//    if (playerShips.shipsLeft() == 0){
//        return board;
//    }
//    PlayerBoard tempBoard(this->playerShips);
//    int rx{}, ry{}, rr{};
//    srand((unsigned)time(nullptr));
//    while (index-- > playerShips.shipsLeft()){
//        rx = rand()%10;
//        ry = rand()%10;
//        rr = rand()%2;
//        Ship type = playerShips.getShipType(shipIndices[index-1]).first;
//
//        if(canPlace(rx, ry, rr, type)){
//            tempBoard.placeShip(rx, ry, rr, type);
//            PLOGD << "Trying to place ship " << type.size << " at (" << rx << "," << ry << ") on board..";
//            return autoPlace(tempBoard, index-1);
//        }
//        else{
//            return tempBoard;
//        }
//    }
//    return tempBoard;
//}

void PlayerBoard::PrintBoardToLog(PlayerBoard board) {
    std::string temp{};
    for (int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            switch(board.getFieldStatus(i-1, j-1)){
                case -1:
                    temp += "D";
                    break;
                case 1:
                    temp += " ";
                    break;
                case 2:
                    temp += "+";
                    break;
                case 3:
                    temp += "O";
                    break;
                case 4:
                    temp += "*";
                    break;
                case 5:
                    temp += "X";
                    break;
                case 0:
                    temp += "U";
                    break;
                default:
                    temp += "D";
                    break;
            }
        }
        PLOGI << temp;
        temp = "";
    }
}

bool PlayerBoard::shipsAlive() {
    for(int r = 0; r < BOARD_SIZE; r++){
        for(int c = 0; c < BOARD_SIZE; c++){
            if(getFieldStatus(r,c) == FieldStatus::Occupied){
                return true;
            }
        }
    }
    return false;
}
