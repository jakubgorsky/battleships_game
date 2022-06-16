//
// Created by kubag on 22/03/2022.
//

#include "GUI.h"
#include <libfort/fort.hpp>

void GUI::display_menu() {
    std::cout<<"=====================================================\n"
             <<" \t\tMENU\n"
             <<"=====================================================\n"
             <<"\t1.Place Ship\n"
             <<"\t2.Shoot\n"
             <<"\t3.Check Ships\n"
             <<"\t4.Check field status\n"
             <<"\t0.Exit\n";
}

void GUI::GUI_HANDLER() {
    //Will add mutex check
    int choice{}, x{}, y{}, rotation{};
    ShipType temp;
    while(true){
        system("cls");
        display_menu();
        std::cin>>choice;
        switch(choice){
            case 1:
                system("cls");
                std::cout << "Provide coordinates: \n"
                    << "X: ";
                std::cin >> x;
                std::cout << "\nY: ";
                std::cin >> y;
                std::cout << "\nProvide rotation (0 - vertical, 1 - horizontal): ";
                std::cin >> rotation;
                std::cout << "\nChoose ship type:"
                        << "\n\t Submarine (size 1): 1"
                        << "\n\t Destroyer (size 2): 2"
                        << "\n\t Cruiser (size 3): 3"
                        << "\n\t Battleship (size 4): 4"
                        << "\n\t Carrier (size 5): 5"
                        << "\nSelection: ";
                std::cin >> temp.size;
                try {
                    playerBoard.placeShip(x, y, rotation, temp);
                }
                catch(std::exception &e){
                    std::cout << e.what() << std::endl;
                }
                std::cout << "Press a key to continue...";
                _getwch();
                break;
            case 0:
                return;
            default:
                return;
        }
    }
}

void GUI::PRINT_BOARD(){
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
            switch(playerBoard.getFieldStatus(i-1, j-1)){
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

GUI::GUI(PlayerBoard &playerBoard, PlayerBoard &enemyBoard, Ships &playerShips, Ships &enemyShips)
        : playerBoard(playerBoard), enemyBoard(enemyBoard), playerShips(playerShips), enemyShips(enemyShips){
}
