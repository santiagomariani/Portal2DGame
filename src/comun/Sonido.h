//
// Created by santi on 13/06/19.
//

#ifndef SONIDO_H
#define SONIDO_H


#include <string>
#include <SDL2/SDL_mixer.h>

class Sonido {
private:
    Mix_Chunk *sonido;
    int canal;
public:
    Sonido(std::string &nombre_archivo, int canal);
    Sonido(Sonido &&otro);
    Sonido& operator=(Sonido &&otro);
    void setearVolumen(uint8_t volumen);
    void parar();
    void pausar();
    void reproducirUnaVez();
    void reproducirEnLoop();
    ~Sonido();
};


#endif //SONIDO_H
