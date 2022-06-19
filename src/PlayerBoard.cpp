//
// Created by jack on 21/03/2022.
//

#include <plog/Log.h>
#include "PlayerBoard.h"
#include <random>
#include <memory>

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
    if ( x < 0 || y < 0 || x > BOARD_SIZE || y > BOARD_SIZE){
        PLOGE << "[ERROR] Specified coordinates land outside board";
        return false;
    }
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

//1. Get next ship
//2. Get random cell and orientation
//3. Try to fit ship (find any conflicts)
//3a. If ship doesn't fit there, **delete all ships and start over**
//3b. If ship fits, get another ship (goto 1)

int shipIndices[7] = { 0, 0, 1, 1, 2, 3, 4};

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<double> dist(0.0, 10.0);

PlayerBoard *PlayerBoard::autoPlace(PlayerBoard& board, int index) {
    if(tempBoard == nullptr){
        tempBoard = new PlayerBoard(playerShips);
    }
    int currentShips = playerShips.shipsLeft();
    if (currentShips == 0 || index == 0){
        return &board;
    }
    Ship type = playerShips.getShipType(shipIndices[index-1]).first;
    int rx, ry, rr;
    rx = floor(dist(mt));
    ry = floor(dist(mt));
    rr = floor(dist(mt));
    FieldStatus statusToSet = getFieldStatus(rx, ry);
    while (!tempBoard->canPlace(rx, ry, rr, type) || statusToSet == Default || statusToSet == Unavailable){
        PLOGD << "Trying to place ship of type " << type.name << " on field (" << rx << "," << ry << ") with rotation " << rr;
        rx = floor(dist(mt));
        ry = floor(dist(mt));
        rr = floor(dist(mt));
        statusToSet = getFieldStatus(rx, ry);
    }
    tempBoard->placeShip(rx, ry, rr, type);
    if (playerShips.shipsLeft() == 0){
        PLOGD << "Returning board...";
        return tempBoard;
    }
    if(currentShips - 1 == playerShips.shipsLeft()){
        PLOGD << "Going recursive...";
        return autoPlace(reinterpret_cast<PlayerBoard &>(*tempBoard), index-1);
    }
    else{
        PLOGD << "Returning nullptr...";
        return nullptr;
    }
}

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
