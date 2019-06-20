
#ifndef SONIDO_H
#define SONIDO_H


#include <string>
#include <SDL2/SDL_mixer.h>

class Sonido {
private:
    Mix_Chunk *sonido;
    int canal;

public:
    // Se carga el sonido .WAV.
    Sonido(std::string &nombre_archivo, int canal);
    Sonido(Sonido &&otro);
    Sonido& operator=(Sonido &&otro);
    // Setea el volumen de sonido (Maximo: 128). Cambia el volumen del canal
    // indicado al momento de crear el sonido.
    void setearVolumen(uint8_t volumen);
    // Para el sonido (para el canal).
    void parar();
    // Pausa el sonido (pausa el canal).
    void pausar();
    // Reproduce el sonido una vez.
    void reproducirUnaVez();
    // Reproduce el sonido en loop (cuando termina vuelve a comenzar).
    void reproducirEnLoop();
    ~Sonido();
};


#endif //SONIDO_H
