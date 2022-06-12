//
// Created by Jakub Górski on 12/06/2022.
//

#ifndef BATTLESHIPS_GAME_GAMEMASTER_H
#define BATTLESHIPS_GAME_GAMEMASTER_H

#include <SDL.h>
#include <plog/Log.h>

#include "GameObject.h"

class GameMaster {
public:
    GameMaster() = default;

    ~GameMaster() = default;

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    inline bool running() const { return isRunning; }

    static SDL_Renderer* renderer;
private:
    bool isRunning{};
    SDL_Texture* texture;
    SDL_Window *window{};
};

#endif //BATTLESHIPS_GAME_GAMEMASTER_H
