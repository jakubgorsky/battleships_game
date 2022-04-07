//
// Created by kubag on 22/03/2022.
//

#ifndef BATTLESHIPS_GAEM_GUI_H
#define BATTLESHIPS_GAEM_GUI_H

#include <iostream>
#include "PlayerBoard.h"

class GUI {
private:
    PlayerBoard &playerBoard;
    Ships &playerShips;
    void display_menu();
public:
    GUI(PlayerBoard &playerBoard, Ships &playerShips);
    void GUI_HANDLER();
    void PRINT_BOARD();
};

#endif //BATTLESHIPS_GAEM_GUI_H
