//
// Created by Jakub Górski on 17/06/2022.
//

#ifndef BATTLESHIPS_GAME_TEXT_H
#define BATTLESHIPS_GAME_TEXT_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class Text {
public:
    Text() = default;
    Text(const std::string &font_Path, int font_size, const std::string &message, const SDL_Color &color);

    void display(int x, int y) const;

    static SDL_Texture* loadFont(const std::string &font_Path, int font_size, const std::string &message, const SDL_Color &color);

protected:
private:
    SDL_Texture *textTexture = nullptr;
    mutable SDL_Rect textRect{};
    SDL_Rect *srcRect = nullptr;
};
#endif //BATTLESHIPS_GAME_TEXT_H
