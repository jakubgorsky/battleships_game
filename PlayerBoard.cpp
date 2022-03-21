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