#include <string>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "textura.h"
#include "ventana.h"
#include "sdl_exception.h"

Textura::Textura() {
    this->renderizador = nullptr;
    this->textura = nullptr;
    this->ancho = 0;
    this->alto = 0;
}

Textura::Textura(const std::string &nombre_archivo, const Ventana &ventana)
    : renderizador(ventana.obtenerRenderizador()) {
    this->textura = cargarTextura(nombre_archivo);
    SDL_QueryTexture(textura, nullptr, nullptr, &ancho, &alto);
}

Textura& Textura::operator=(Textura &&otro) {
    if (this == &otro) {
        return *this;
    }
    if (this->textura) {
        SDL_DestroyTexture(this->textura);
    }
    this->textura = otro.textura;
    this->renderizador = otro.renderizador;
    this->ancho = otro.ancho;
    this->alto = otro.alto;

    otro.textura = nullptr;
    otro.renderizador = nullptr;
    otro.ancho = 0;
    otro.alto = 0;
    return *this;
}

Textura::Textura(Textura &&otro) {
    this->textura = otro.textura;
    this->renderizador = otro.renderizador;
    this->ancho = otro.ancho;
    this->alto = otro.alto;

    otro.textura = nullptr;
    otro.renderizador = nullptr;
    otro.ancho = 0;
    otro.alto = 0;
}

SDL_Texture* Textura::cargarTextura(const std::string &nombre_archivo) {
    SDL_Texture* textura = IMG_LoadTexture(this->renderizador, nombre_archivo.c_str());
    if (!textura) {
        throw SdlException("Error al cargar la textura.", SDL_GetError());
    }
    return textura;
}

void Textura::renderizar(const SDL_Rect *fuente,
                         const SDL_Rect *destino,
                         double angulo,
                         SDL_Point *centro,
                         SDL_RendererFlip espejado) const {
    SDL_RenderCopyEx(this->renderizador,
            this->textura,
            fuente,
            destino,
            angulo,
            centro,
            espejado);
}

int Textura::obtenerAncho() {
    return ancho;
}

int Textura::obtenerAlto() {
    return alto;
}

void Textura::setearColorModulacion(uint8_t r, uint8_t g, uint8_t b) {
    SDL_SetTextureColorMod(textura, r, g, b);
}

void Textura::setearAlpha(uint8_t alpha) {
    SDL_SetTextureAlphaMod(textura, alpha);
}

Textura::~Textura() {
    if (this->textura) {
        SDL_DestroyTexture(this->textura);
        this->textura = nullptr;
    }
}
