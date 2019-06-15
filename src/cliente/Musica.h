//
// Created by santi on 14/06/19.
//

#ifndef MUSICA_H
#define MUSICA_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Musica {
private:
    Mix_Music *musica;
public:
    Musica(std::string nombre_archivo);
    void reproducirUnaVez();
    void reproducirEnLoop();
    void setearVolumen(uint8_t volumen);
    void despausar();
    void pausar();
    void parar();
    bool seEstaReproduciendo();
    ~Musica();

};


#endif //MUSICA_H
