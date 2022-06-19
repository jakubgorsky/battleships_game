//
// Created by jack on 21/03/2022.
//

#ifndef BATTLESHIPS_GAEM_PLAYERBOARD_H
#define BATTLESHIPS_GAEM_PLAYERBOARD_H

#include "Ship.h"
#include "Definitions.h"

class PlayerBoard {
private:
    FieldStatus Board[BOARD_SIZE][BOARD_SIZE]{};
    void INITIALIZE_BOARD();
    bool canPlace(int x, int y, int rotation, const Ship& shipType);
    Ships &playerShips;
    PlayerBoard *tempBoard;
public:
    PlayerBoard(Ships &playerShips) : playerShips(playerShips) {
        INITIALIZE_BOARD();
    }
    //DEBUG ONLY
    void setFieldStatus(int x, int y, FieldStatus status);

    FieldStatus getFieldStatus(int x, int y);
    FieldStatus shootField(int x, int y);
    bool placeShip(int x, int y, int rotation, const Ship& shipType);
    PlayerBoard* autoPlace(PlayerBoard &board, int index = 7);

    bool shipsAlive();

    void PrintBoardToLog(PlayerBoard board);

    ~PlayerBoard() = default;
};

#endif //BATTLESHIPS_GAEM_PLAYERBOARD_H
