//
// Created by Jakub Górski on 11/06/2022.
//

#ifndef BATTLESHIPS_GAME_INPUTHANDLER_H
#define BATTLESHIPS_GAME_INPUTHANDLER_H

#include <SDL.h>
#include "EventHandler.h"

class InputHandler {
private:
    SDL_Event* m_Event;
    EventHandler m_EH;
public:
    InputHandler(SDL_Event* e);
    ~InputHandler() = default;

    void ParseKeyInput(SDL_Keycode keyDown);
};

#endif //BATTLESHIPS_GAME_INPUTHANDLER_H
