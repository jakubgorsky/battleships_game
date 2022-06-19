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
#include "PlayerBoard.h"
#include "Ship.h"

Map* map;
Map* gridMap;

SDL_Renderer* GameMaster::renderer = nullptr;
SDL_Event GameMaster::event;
Manager manager;
int mX, mY;
double rotation;
Text text;
Text *titleText, *shiptypehelp, *shootrotate, *skip, *quit, *turn;
Entity &textBG(manager.addEntity());
Ships player, ai;
PlayerBoard *playerBoard = new PlayerBoard(player);
PlayerBoard *aiBoard = new PlayerBoard(ai);
int shipType = 0;
Entity &boardHoverMarker(manager.addEntity());
bool backgroundExists = false;
bool gameOver = false;

void GameMaster::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {

    setGameState(GAMESTATE::INIT);
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
    gridMap->LoadMap(DEF_GRID_R);

    //ecs impl

    boardHoverMarker.addComponent<TransformComponent>(64,64);
    boardHoverMarker.addComponent<SpriteComponent>("../res/textures/whitesq.png");
    boardHoverMarker.getComponent<SpriteComponent>().setTransparent();
    boardHoverMarker.addGroup(groupMarkings);

    auto *tempBoard = aiBoard->autoPlace(*aiBoard);
    titleText = new Text("../res/fonts/ubuntu.ttf", 24, "controls:", {255,255,255,255});
    shiptypehelp = new Text("../res/fonts/ubuntu.ttf", 24, "1-5 selects ship type to place", {255,255,255,255});
    shootrotate = new Text("../res/fonts/ubuntu.ttf", 24, "LMB to place / shoot, RMB to rotate", {255,255,255,255});
    skip = new Text("../res/fonts/ubuntu.ttf", 24, "Space to let the AI make a turn", {255,255,255,255});
    quit = new Text("../res/fonts/ubuntu.ttf", 24, "ESC to quit", {255, 255, 255, 255});
    turn = new Text("../res/fonts/ubuntu.ttf", 40, "Your turn", {255,255,255,255});
    textBG.addComponent<TransformComponent>(5, 740, shootrotate->getRect().w+20, shiptypehelp->getRect().h*5+10, 1, 1);
    textBG.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/blacksq.png"));
    textBG.getComponent<SpriteComponent>().setTransparent();
    textBG.getComponent<SpriteComponent>().setAlpha(150);
    textBG.addGroup(groupGrid);
    aiBoard = tempBoard;
    if(tempBoard == nullptr){
        PLOGE << "Didn't generate random board";
    }
    setGameState(GAMESTATE::PLACING);
}

void GameMaster::handleEvents() {
    int x, y;
    SDL_PollEvent(&event);
    SDL_PumpEvents();
    SDL_GetMouseState(&mX, &mY);
    x = (int)(0 + 64 * floor((double)mX / 64));
    y = (int)(0 + 64 * floor((double)mY / 64));
    switch(event.type){
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym) {
                case SDLK_1:
                    shipType = 0;
                    break;
                case SDLK_2:
                    shipType = 1;
                    break;
                case SDLK_3:
                    shipType = 2;
                    break;
                case SDLK_4:
                    shipType = 3;
                    break;
                case SDLK_5:
                    shipType = 4;
                    break;
                case SDLK_ESCAPE:
                    isRunning = false;
                    break;
                case SDLK_SPACE:
                    if(GAME_STATE == GAMESTATE::AI_TURN){
                        int aiX = rand()%10;
                        int aiY = rand()%10;
                        FieldStatus statusToChange = playerBoard->shootField(aiX, aiY);
                        while(statusToChange == Unavailable || statusToChange == Default) {
                            aiX = rand()%10;
                            aiY = rand()%10;
                            statusToChange = playerBoard->shootField(aiX, aiY);
                        }
                        playerBoard->setFieldStatus(aiX, aiY, playerBoard->shootField(aiX, aiY));
                        if(statusToChange == Hit){
                            Entity& obj(manager.addEntity());
                            obj.addComponent<TransformComponent>((aiY+14)*64, (aiX+1)*64);
                            obj.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/hit.png"));
                            obj.getComponent<SpriteComponent>().setTransparent();
                            obj.getComponent<SpriteComponent>().setAlpha(255);
                            obj.addGroup(groupMarkings);
                        }
                        if(statusToChange == Missed) {
                            Entity& obj(manager.addEntity());
                            obj.addComponent<TransformComponent>((aiY+14)*64, (aiX+1)*64);
                            obj.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/missed.png"));
                            obj.getComponent<SpriteComponent>().setTransparent();
                            obj.getComponent<SpriteComponent>().setAlpha(255);
                            obj.addGroup(groupMarkings);
                        }
                        setGameState(GAMESTATE::PLAYER_TURN);
                        turn->setText("Your turn");
                    }
                    break;
                default:
                    break;
            }
            break;
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_RIGHT){
                if (rotation == 1)
                    rotation = 0;
                else
                    rotation = 1;
                PLOGI << rotation;
                break;
            }
            if(((x < 64 || x > 703) && GAME_STATE != GAMESTATE::PLACING) || (x < 896 && GAME_STATE == GAMESTATE::PLACING) || x > 1535 || y < 64 || y > 703){
                break;
            }
            if(GAME_STATE == GAMESTATE::PLACING &&!(x > 896 && x < 1536 && playerBoard->getFieldStatus((y/64)-1, (x/64)-14) == Occupied)) {
                if(playerBoard->placeShip((y/64)-1,(x/64)-14, (int)rotation, player.getShipType(shipType).first)){
                    int t = 0;
                    for (const auto& i : player.getShipType(shipType).first.textures) {
                        Entity &obj(manager.addEntity());
                        if((int)rotation%2){
                            obj.addComponent<TransformComponent>((float) (x+t*64), (float) y);
                        }
                        else{
                            obj.addComponent<TransformComponent>((float) x, (float) (y+t*64));
                        }
                        t++;

                        obj.addComponent<SpriteComponent>(TextureManager::LoadTexture(i.c_str()));
                        obj.getComponent<SpriteComponent>().setTransparent();
                        obj.getComponent<SpriteComponent>().setAlpha(255);
                        if((int)rotation%2){
                            if(t == player.getShipType(shipType).first.size){
                                obj.getComponent<SpriteComponent>().rotate((rotation+1)*90);
                            }
                            else{
                                obj.getComponent<SpriteComponent>().rotate((rotation-1)*90);
                            }
                        }
                        else{
                            if(t == player.getShipType(shipType).first.size){
                                obj.getComponent<SpriteComponent>().rotate((rotation-1)*90);
                            }
                            else{
                                obj.getComponent<SpriteComponent>().rotate((rotation+1)*90);
                            }
                        }

                        obj.addGroup(groupShips);
                    }
                }
                if(player.shipsLeft() == 0){
                    GAME_STATE = GAMESTATE::AI_TURN;
                    gridMap->LoadMap(DEF_GRID_L);
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(GAME_STATE == GAMESTATE::PLAYER_TURN && mX > 63 && mX < 703 && mY > 63 && mY < 703) {
                FieldStatus statusToChange = aiBoard->shootField((y / 64) - 1, (x / 64) - 1);
                if (statusToChange != Unavailable && statusToChange != Default) {
                    aiBoard->setFieldStatus((y / 64) - 1, (x / 64) - 1, statusToChange);
                    if(statusToChange == Hit){
                        Entity& obj(manager.addEntity());
                        obj.addComponent<TransformComponent>(x, y);
                        obj.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/hit.png"));
                        obj.getComponent<SpriteComponent>().setTransparent();
                        obj.getComponent<SpriteComponent>().setAlpha(255);
                        obj.addGroup(groupMarkings);
                    }
                    if(statusToChange == Missed) {
                        Entity& obj(manager.addEntity());
                        obj.addComponent<TransformComponent>(x, y);
                        obj.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/missed.png"));
                        obj.getComponent<SpriteComponent>().setTransparent();
                        obj.getComponent<SpriteComponent>().setAlpha(255);
                        obj.addGroup(groupMarkings);
                    }
                    setGameState(GAMESTATE::AI_TURN);
                    turn->setText("AI turn");
                }
            }
            break;
    }
    if(GAME_STATE == GAMESTATE::PLACING && (mX > 896 && mX < 1536 && mY > 63 && mY < 704)) {
        boardHoverMarker.getComponent<SpriteComponent>().setAlpha(150);
        boardHoverMarker.getComponent<TransformComponent>().position.x = (float)x;
        boardHoverMarker.getComponent<TransformComponent>().position.y = (float)y;
        if ((int) rotation % 2) {
            boardHoverMarker.getComponent<TransformComponent>().scaleX = shipType+1;
            boardHoverMarker.getComponent<TransformComponent>().scaleY = 1;
        }
        else{
            boardHoverMarker.getComponent<TransformComponent>().scaleX = 1;
            boardHoverMarker.getComponent<TransformComponent>().scaleY = shipType+1;
        }
    }
    else if(GAME_STATE == GAMESTATE::PLAYER_TURN && (mX > 63 && mX < 704 && mY > 63 && mY < 704)) {
        boardHoverMarker.getComponent<SpriteComponent>().setAlpha(150);
        boardHoverMarker.getComponent<TransformComponent>().position.x = (float)x;
        boardHoverMarker.getComponent<TransformComponent>().position.y = (float)y;
        boardHoverMarker.getComponent<TransformComponent>().scaleX = 1;
        boardHoverMarker.getComponent<TransformComponent>().scaleY = 1;
    }
    else
        boardHoverMarker.getComponent<SpriteComponent>().setAlpha(0);
}

void GameMaster::update() {
    if(!aiBoard->shipsAlive() && GAME_STATE!=GAMESTATE::PLACING && !gameOver){
        setGameState(GAMESTATE::WON);
        Text textWon("../res/fonts/ubuntu.ttf", 80, "You won!", {0, 255, 0, 255});
        text = textWon;
        gameOver = true;
    }
    if(!playerBoard->shipsAlive() && GAME_STATE!=GAMESTATE::PLACING && !gameOver){
        setGameState(GAMESTATE::LOST);
        Text textWon("../res/fonts/ubuntu.ttf", 80, "You lost!", {255, 0, 0, 255});
        text = textWon;
        gameOver = true;
    }
    if((GAME_STATE == GAMESTATE::WON || GAME_STATE == GAMESTATE::LOST) && !backgroundExists){
        Entity& background(manager.addEntity());
        background.addComponent<TransformComponent>(0, 0, 1600, 900, 25, 15);
        background.addComponent<SpriteComponent>(TextureManager::LoadTexture("../res/textures/blacksq.png"));
        background.getComponent<SpriteComponent>().setTransparent();
        background.getComponent<SpriteComponent>().setAlpha(100);
        background.addGroup(groupMarkings);
        backgroundExists = true;
    }

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
//    titleText, *shiptypehelp, *shootrotate, *skip, *quit
    turn->display((1600-turn->getRect().w)/2, 0);
    titleText->display(15, (720+titleText->getRect().h*1));
    shiptypehelp->display(15, (720+titleText->getRect().h*2));
    shootrotate->display(15, (720+titleText->getRect().h*3));
    skip->display(15, (720+titleText->getRect().h*4));
    quit->display(15, (720+quit->getRect().h*5));
    for (auto& m : markings){
        m->draw();
    }

    if(GAME_STATE == GAMESTATE::WON || GAME_STATE == GAMESTATE::LOST){
        text.display((1600-text.getRect().w)/2, (900-text.getRect().h)/2);
    }
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