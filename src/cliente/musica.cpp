
#include <SdlException.h>
#include "Musica.h"

Musica::Musica(std::string nombre_archivo) {
    musica = Mix_LoadMUS(nombre_archivo.c_str());
    if (!musica) {
        throw SdlException("Error en la inicialización de musica: %s\n",
                Mix_GetError());
    }
}

void Musica::reproducirUnaVez() {
    Mix_PlayMusic(musica, 0);
}

void Musica::reproducirEnLoop() {
    Mix_PlayMusic(musica, -1);
}

void Musica::despausar() {
    Mix_ResumeMusic();
}

void Musica::pausar() {
    Mix_PauseMusic();
}

void Musica::parar() {
    Mix_HaltMusic();
}

bool Musica::seEstaReproduciendo() {
    return Mix_PlayingMusic() == 0;
}

void Musica::setearVolumen(uint8_t volumen) {
    Mix_VolumeMusic(volumen);
}

Musica::~Musica() {
    if (musica) {
        Mix_FreeMusic(musica);
        musica = nullptr;
    }
}
