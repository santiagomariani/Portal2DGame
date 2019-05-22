#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "SdlTexture.h"
#include "SdlWindow.h"
#include "SdlException.h"

SdlTexture::SdlTexture() {
    this->renderer = nullptr;
    this->texture = nullptr;
    this->width = 0;
    this->height = 0;
}

SdlTexture::SdlTexture(const std::string &filename, const SdlWindow &window)
    : renderer(window.getRenderer()) {
    this->texture = loadTexture(filename);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

SdlTexture& SdlTexture::operator=(SdlTexture &&other) {
    if (this == &other) {
        return *this;
    }
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
    }
    this->texture = other.texture;
    this->renderer = other.renderer;
    this->width = other.width;
    this->height = other.height;

    other.texture = nullptr;
    other.renderer = nullptr;
    other.width = 0;
    other.height = 0;
}

SdlTexture::SdlTexture(SdlTexture &&other) {
    this->texture = other.texture;
    this->renderer = other.renderer;
    this->width = other.width;
    this->height = other.height;

    other.texture = nullptr;
    other.renderer = nullptr;
    other.width = 0;
    other.height = 0;
}

SDL_Texture* SdlTexture::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura.", SDL_GetError());
    }
    return texture;
}

int SdlTexture::render(const SDL_Rect *src,
        const SDL_Rect *dest,
        double angle,
        SDL_Point *center,
        SDL_RendererFlip flip) const {
    SDL_RenderCopyEx(this->renderer,
            this->texture,
            src,
            dest,
            angle,
            center,
            flip);
}

int SdlTexture::getWidth() {
    return width;
}

int SdlTexture::getHeight() {
    return height;
}

SdlTexture::~SdlTexture() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}
