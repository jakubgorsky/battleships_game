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

void GUI::PRINT_BOARD(PlayerBoard board){
    fort::utf8_table table;
    table.set_cell_text_align(fort::text_align::center);
    table << fort::header;
    table[0][0] = "X";
    std::string temp = "";
    for (int i = 1; i <= 10; i++){
        temp = char(64+i);
        table[0][i] = temp;
    }
    table << fort::endr;

    for (int i = 1; i <= 10; i++){
        temp = char(48+i);
        if (i == 10) { temp = "10";}
        table[i][0] = temp;
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
            table[i][j] = temp;
        }
        table << fort::endr;
    }
    std::cout << table.to_string() << std::endl;
}