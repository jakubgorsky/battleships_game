//
// Created by Jakub Górski on 11/06/2022.
//

#include "EventHandler.h"
#include <SDL_keycode.h>

EventHandler::EventHandler(SDL_Event* ev)
    : ev(ev)
{

}

EventHandler::~EventHandler() = default;

bool EventHandler::OnExit(bool& running) {
    while(SDL_PollEvent(ev) != 0 && ev->type == SDL_QUIT){
            running = false;
            SDL_Quit();
            return true;
    }
    return false;
}

SDL_Keycode EventHandler::OnKeyDown(){
    while(SDL_PollEvent(ev) != 0 && ev->type == SDL_KEYDOWN){
        return ev->key.keysym.sym;
    }
    return SDLK_WWW;
}