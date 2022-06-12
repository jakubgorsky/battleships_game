//
// Created by Jakub Górski on 12/06/2022.
//

#include "GameMaster.h"
#include "Definitions.h"

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <fstream>

int main(int argc, char *argv[]){

    Uint32 frameStart{};
    int frameTime{};

    std::fstream fs("../log.txt", std::ios::out | std::ios::trunc);
    fs.close();
    plog::init(plog::debug, "../log.txt");

    GameMaster *gameMaster = new GameMaster();

    gameMaster->init(SCREEN_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while(gameMaster->running()){

        frameStart = SDL_GetTicks();

        gameMaster->handleEvents();
        gameMaster->update();
        gameMaster->render();

        frameTime = SDL_GetTicks() - frameStart;

        if(FRAME_DELAY > frameTime){
            SDL_Delay(FRAME_DELAY - frameTime);
        }

    }

    gameMaster->clean();

    return 0;
}