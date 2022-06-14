//
// Created by Jakub Górski on 11/06/2022.
//

#include "GameMaster.h"
#include <SDL_image.h>
#include "Map.h"
#include "ECS.h"
#include "Components.h"

Map* map;
Map* grid;

int gridMap[15][25]{
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, TEX::gridtl, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridtr, -1, -1, -1, TEX::gridtl, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridt, TEX::gridtr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1, -1, -1, TEX::gridml, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridm, TEX::gridmr, -1},
        {-1, TEX::gridbl, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridbr, -1, -1, -1, TEX::gridbl, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridb, TEX::gridbr, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

SDL_Renderer* GameMaster::renderer = nullptr;
Manager manager;
auto& newEntity(manager.addEntity());

void GameMaster::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    PLOGD << "Initializing game subsystems...";

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        PLOGD << "Failed initializing subsystems!\n";
        isRunning = false;
        return;
    }

    PLOGD << "Game subsystems initialized successfully.";
    PLOGD << "Initializing window...";

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(!window){
        PLOGD << "Failed initializing window!";
        isRunning = false;
        return;
    }

    PLOGD << "Window initialized successfully.";
    PLOGD << "Initializing renderer...";

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        PLOGD << "Failed initializing renderer!";
        isRunning = false;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;
    PLOGD << "Renderer initialized successfully.";
    PLOGD << "Initializing renderer...";

    PLOGD << "Loading map texture...";

    map = new Map();
    grid = new Map();
    grid->LoadMap(gridMap);

    newEntity.addComponent<PositionComponent>();
}

void GameMaster::handleEvents() {
    SDL_Event e;
    SDL_PollEvent(&e);
    switch(e.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
}

void GameMaster::update() {
    manager.update();
//    PLOGD << "(" << newEntity.getComponent<PositionComponent>().x() << ", " << newEntity.getComponent<PositionComponent>().y() << ")";
}

void GameMaster::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    grid->DrawMap();
    SDL_RenderPresent(renderer);
}

void GameMaster::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    PLOGD << "Cleaned subsystems.";
}