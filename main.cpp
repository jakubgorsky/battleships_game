//
// Created by jack on 21/03/2022.
//
#include <iostream>
#include "PlayerBoard.h"
#include "Ship.h"
// debug only lol
int main() {
    int x, y;
    FieldStatus status;
    x = y = 1;
    status = Hit;
    PlayerBoard b;
    b.setFieldStatus(x, y, status);


    std::cout << b.getFieldStatus(x, y);
}