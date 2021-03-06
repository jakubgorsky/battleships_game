//
// Created by Jakub Górski on 17/06/2022.
//

#include "GameMaster.h"
#include "TextureManager.h"
#include "Text.h"
#include <plog/Log.h>

Text::Text(const std::string &font_Path, int font_size, const std::string &message, const SDL_Color &color)
    : path(font_Path), font_size(font_size), message(message), color(color){
    textTexture = loadFont(font_Path, font_size, message, color);
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::display(int x, int y) const {
    textRect.x = x;
    textRect.y = y;
    TextureManager::Draw(textTexture, srcRect, &textRect);
}

SDL_Texture *Text::loadFont(const std::string &font_path, int font_size, const std::string &message, const SDL_Color &color) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (font == nullptr){
        PLOGE << "Failed to load font! " << TTF_GetError();
        return nullptr;
    }
    auto text_surface = TTF_RenderText_Solid(font, message.c_str(), color);
    if(text_surface == nullptr){
        PLOGE << "Failed to create text surface! " << TTF_GetError();
        return nullptr;
    }
    auto text_texture = SDL_CreateTextureFromSurface(GameMaster::renderer, text_surface);
    if(text_texture == nullptr){
        PLOGE << "Failed to create text texture! " << SDL_GetError();
        return nullptr;
    }
//    SDL_FreeSurface(text_surface);
    return text_texture;
}

void Text::setText(const std::string &message) {
    textTexture = loadFont(path, font_size, message, color);
    this->message = message;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::setSize(int font_size) {
    textTexture = loadFont(path, font_size, message, color);
    this->font_size = font_size;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::setFont(const std::string &font_Path) {
    textTexture = loadFont(path, font_size, message, color);
    this->path = font_Path;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::setColor(const SDL_Color &color) {
    textTexture = loadFont(path, font_size, message, color);
    this->color = color;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
}
