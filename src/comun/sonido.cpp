
#include <sdl_exception.h>
#include "sonido.h"

Sonido::Sonido(std::string &nombre_archivo, int canal) : canal(canal) {
    sonido = Mix_LoadWAV(nombre_archivo.c_str());
    if (!sonido) {
        throw SdlException("Error en la inicialización de sonido: %s\n",
                Mix_GetError());
    }
}

void Sonido::setearVolumen(uint8_t volumen) {
    Mix_VolumeChunk(sonido, volumen);
}

void Sonido::reproducirUnaVez() {
    if (Mix_Paused(canal)) {
        Mix_Resume(canal);
    } else {
        Mix_PlayChannel(canal, sonido, 0);
    }
}

void Sonido::reproducirEnLoop() {
    if (Mix_Paused(canal)) {
        Mix_Resume(canal);
    } else {
        Mix_PlayChannel(canal, sonido, -1);
    }
}

void Sonido::pausar() {
    Mix_Pause(canal);
}

void Sonido::parar() {
    Mix_HaltChannel(canal);
}

Sonido::~Sonido() {
    if (sonido) {
        Mix_FreeChunk(sonido);
        sonido = nullptr;
    }
}

Sonido::Sonido(Sonido &&otro) {
    sonido = otro.sonido;
    canal = otro.canal;
    otro.sonido = nullptr;
    otro.canal = -1;
}

Sonido &Sonido::operator=(Sonido &&otro) {
    if (this == &otro) {
        return *this;
    }
    sonido = otro.sonido;
    canal = otro.canal;
    otro.canal = -1;
    otro.sonido = nullptr;
}
