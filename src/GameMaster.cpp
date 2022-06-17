//
// Created by Jakub Górski on 11/06/2022.
//

#include "GameMaster.h"
#include <SDL_image.h>
#include <cmath>
#include "Map.h"
#include "Text.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include <SDL_ttf.h>

Map* map;
Map* gridMap;

SDL_Renderer* GameMaster::renderer = nullptr;
SDL_Event GameMaster::event;
Manager manager;
Entity& whiteRect(manager.addEntity());
int mX, mY;
bool placedL[2][10][10];
bool placedR[2][10][10];
double rotation;
Text text;

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
    if(TTF_Init() < 0){
        PLOGE << "failed initializing TTF! " << TTF_GetError();
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
    gridMap = new Map();
    gridMap->LoadMap(DEF_GRID_L);

    for (auto& i : placedL){
        for (auto& r : i){
            for (auto& c : r){
                c = false;
            }
        }
    }
    for (auto& i : placedR){
        for (auto& r : i){
            for (auto& c : r){
                c = false;
            }
        }
    }

    //ecs impl

    whiteRect.addComponent<TransformComponent>(64, 64);
    whiteRect.addComponent<SpriteComponent>("../res/textures/whitesq.png");
    whiteRect.getComponent<SpriteComponent>().setTransparent();
    whiteRect.getComponent<SpriteComponent>().setAlpha(100);
    whiteRect.addGroup(groupMarkings);
    Text text1("../res/fonts/Unibody_8_Bold.ttf", 40, "Test message", {255, 255, 255, 255});
    text = text1;
}

void GameMaster::handleEvents() {
    int x, y;
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_r){
                if(rotation >= 360)
                    rotation = 0;
                rotation+=90;
                PLOGI << rotation;
                break;
            }
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_PumpEvents();
            SDL_GetMouseState(&mX, &mY);
            x = (int)(0 + 64 * floor((double)mX / 64));
            y = (int)(0 + 64 * floor((double)mY / 64));
            if(x < 64 || (x > 640 && x < 896) || x > 1535 || y < 64 || y > 640){
                break;
            }
            if((x/64)-1 < 10 && placedL[0][(x/64)-1][(y/64)-1]){
                break;
            }
            else if(x > 896 && x < 1536 && placedR[1][(x/64)-14][(y/64)-1]){
                break;
            }
            else {
                Entity& obj(manager.addEntity());
                obj.addComponent<TransformComponent>((float)x, (float)y);
                obj.addComponent<SpriteComponent>(("../res/textures/tiles/" + std::to_string(TEX::shipmid) + ".png").c_str());
                obj.getComponent<SpriteComponent>().setTransparent();
                obj.getComponent<SpriteComponent>().setAlpha(255);
                obj.getComponent<SpriteComponent>().rotate(rotation);
                obj.addGroup(groupShips);
                if(x < 704){
                    placedL[0][(x/64)-1][(y/64)-1] = true;
                }
                else if(x > 704 && x < 1536){
                    placedR[1][x-14][y-1] = true;
                }
                break;
            }
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
}

auto& tiles(manager.getGroup(groupLabels::groupMap));
auto& grid(manager.getGroup(groupLabels::groupGrid));
auto& ships(manager.getGroup(groupLabels::groupShips));
auto& markings(manager.getGroup(groupLabels::groupMarkings));


void GameMaster::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    gridMap->DrawMap();
    for (auto& t : tiles){
        t->draw();
    }
    for (auto& g : grid){
        g->draw();
    }
    for (auto& s : ships){
        s->draw();
    }
    for (auto& m : markings){
        m->draw();
    }
    text.display(50, 50);
    SDL_RenderPresent(renderer);
}

void GameMaster::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    PLOGI << "Cleaned subsystems.";
}

void GameMaster::AddTile(int id, int x, int y) {
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 64, 64, id);
    tile.addGroup(groupMap);
}
