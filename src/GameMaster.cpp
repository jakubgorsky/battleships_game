//
// Created by Jakub Górski on 11/06/2022.
//

#include "GameMaster.h"
#include <SDL_image.h>
#include <cmath>
#include "Map.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Vector2D.h"

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
Entity& whiteRect(manager.addEntity());
int mX, mY;

void GameMaster::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    PLOGI << "Initializing game subsystems...";

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        PLOGE << "Failed initializing subsystems!\n";
        isRunning = false;
        return;
    }

    PLOGI << "Game subsystems initialized successfully.";
    PLOGI << "Initializing window...";

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if(!window){
        PLOGE << "Failed initializing window!";
        isRunning = false;
        return;
    }

    PLOGI << "Window initialized successfully.";
    PLOGI << "Initializing renderer...";

    renderer = SDL_CreateRenderer(window, -1, 0);
    if(!renderer){
        PLOGE << "Failed initializing renderer!";
        isRunning = false;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    isRunning = true;
    PLOGI << "Renderer initialized successfully.";
    PLOGI << "Initializing renderer...";

    PLOGI << "Loading map texture...";

    map = new Map();
    grid = new Map();
    grid->LoadMap(gridMap);

    //ecs impl

    whiteRect.addComponent<TransformComponent>(64, 64);
    whiteRect.addComponent<SpriteComponent>("../res/textures/whitesq.png");
    whiteRect.getComponent<SpriteComponent>().setTransparent();
    whiteRect.getComponent<SpriteComponent>().setAlpha(100);
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
    SDL_PumpEvents();
    SDL_GetMouseState(&mX, &mY);
    if((mX > 63 && mX < 704 && mY > 63 && mY < 704) || (mX > 896 && mX < 1536 && mY > 63 && mY < 704)) {
        whiteRect.getComponent<SpriteComponent>().setAlpha(150);
        whiteRect.getComponent<TransformComponent>().position.x = (float)(0 + 64 * floor((double)mX / 64));
        whiteRect.getComponent<TransformComponent>().position.y = (float)(0 + 64 * floor((double)mY / 64));
    }
    else
        whiteRect.getComponent<SpriteComponent>().setAlpha(0);
    manager.refresh();
    manager.update();
//    PLOGI << "(" << whiteRect.getComponent<TransformComponent>().x() << ", " << whiteRect.getComponent<TransformComponent>().y() << ")";
}

void GameMaster::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    grid->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void GameMaster::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    PLOGI << "Cleaned subsystems.";
}