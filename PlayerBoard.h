//
// Created by jack on 21/03/2022.
//

#ifndef BATTLESHIPS_GAEM_PLAYERBOARD_H
#define BATTLESHIPS_GAEM_PLAYERBOARD_H

const int BOARD_SIZE = 10;

enum FieldStatus {
    Default = -1,
    Free = 1,
    Occupied = 2,
    Missed = 3,
    Hit =  4
};

class PlayerBoard {
private:
    FieldStatus Board[BOARD_SIZE][BOARD_SIZE];
public:
    FieldStatus getFieldStatus(int x, int y);
    //DEBUG ONLY
    void setFieldStatus(int x, int y, FieldStatus status);
    void setShip(int x1, int x2, int y1, int y2);
    FieldStatus shootField(int x, int y);
};


#endif //BATTLESHIPS_GAEM_PLAYERBOARD_H
