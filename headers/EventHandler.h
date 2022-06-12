//
// Created by Jakub Górski on 11/06/2022.
//

#ifndef BATTLESHIPS_GAME_EVENTHANDLER_H
#define BATTLESHIPS_GAME_EVENTHANDLER_H

#include <SDL.h>

class EventHandler {
private:
    SDL_Event* ev;
public:
    explicit EventHandler(SDL_Event* ev);
    ~EventHandler();
    bool OnExit(bool& running);

    SDL_Keycode OnKeyDown();
};

#endif //BATTLESHIPS_GAME_EVENTHANDLER_H
