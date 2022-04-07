//
// Created by kubag on 22/03/2022.
//

#include "GUI.h"
#include "third-party/libfort/fort.hpp"

void GUI::display_menu() {
    std::cout<<"===================================================== \n"
             <<" \t\tMENU \t \n "
             <<"===================================================== \n"
             <<" 1.Place Ship\n"
             <<" 2.Shoot\n"
             <<" 3.Check Ships\n"
             <<" 4.Check field status\n"
             <<" 0.Exit\n";
}

void GUI::GUI_HANDLER() {
    //Will add mutex check
}

void GUI::PRINT_BOARD(PlayerBoard board, Ships playerShips){
    fort::utf8_table boardTable;
    fort::utf8_table shipCount;
    boardTable.set_cell_text_align(fort::text_align::center);
    shipCount.set_cell_text_align(fort::text_align::center);
    shipCount << fort::header;
    boardTable << fort::header;
    boardTable[0][0] = "X";
    std::string temp = "";
    for (int i = 1; i <= 10; i++){
        temp = char(64+i);
        boardTable[0][i] = temp;
    }
    boardTable << fort::endr;

    for (int i = 1; i <= 10; i++){
        temp = char(48+i);
        if (i == 10) { temp = "10";}
        boardTable[i][0] = temp;
        for(int j = 1; j <= 10; j++){
            switch(board.getFieldStatus(i-1, j-1)){
                case -1:
                    temp = "D";
                    break;
                case 1:
                    temp = " ";
                    break;
                case 2:
                    temp = "\u220E";
                    break;
                case 3:
                    temp = "O";
                    break;
                case 4:
                    temp = "*";
                    break;
                case 5:
                    temp = "X";
                    break;
                case 0:
                    temp = "U";
                    break;
                default:
                    temp = "D";
                    break;
            }
//            temp = board.getFieldStatus(i-1, j-1);
            boardTable[i][j] = temp;
        }
        boardTable << fort::endr;
    }
    shipCount[0][0] = "Ships:";
    shipCount[0][0].set_cell_span(2);
    shipCount << fort::endr;
    for (int i = 1; i <= 5; i++){
        std::pair<ShipType, int> tempShip = playerShips.getShipType(i-1);
        shipCount[i][0] = tempShip.first.name;
        shipCount[i][1] = std::to_string(playerShips.getShipCount(i-1));
        shipCount << fort::endr;
    }

    std::cout << boardTable.to_string() << std::endl;
    std::cout << shipCount.to_string() << std::endl;
}