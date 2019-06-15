#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Textura.h"
#include "Ventana.h"
#include "SdlException.h"

Textura::Textura() {
    this->renderer = nullptr;
    this->texture = nullptr;
    this->width = 0;
    this->height = 0;
}

Textura::Textura(const std::string &filename, const Ventana &window)
    : renderer(window.obtenerRenderizador()) {
    this->texture = loadTexture(filename);
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
}

Textura& Textura::operator=(Textura &&other) {
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

Textura::Textura(Textura &&other) {
    this->texture = other.texture;
    this->renderer = other.renderer;
    this->width = other.width;
    this->height = other.height;

    other.texture = nullptr;
    other.renderer = nullptr;
    other.width = 0;
    other.height = 0;
}

SDL_Texture* Textura::loadTexture(const std::string &filename) {
    SDL_Texture* texture = IMG_LoadTexture(this->renderer, filename.c_str());
    if (!texture) {
        throw SdlException("Error al cargar la textura.", SDL_GetError());
    }
    return texture;
}

int Textura::render(const SDL_Rect *src,
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

int Textura::getWidth() {
    return width;
}

int Textura::getHeight() {
    return height;
}

void Textura::setearColorModulacion(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(texture, r, g, b);
}

Textura::~Textura() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture = nullptr;
    }
}
