//
// Created by kubag on 22/03/2022.
//

#ifndef BATTLESHIPS_GAEM_GUI_H
#define BATTLESHIPS_GAEM_GUI_H

#include <iostream>
#include "PlayerBoard.h"

class GUI {
private:
    void display_menu();
public:
    void GUI_HANDLER();
    void PRINT_BOARD(PlayerBoard board, Ships playerShips);
};

#endif //BATTLESHIPS_GAEM_GUI_H
