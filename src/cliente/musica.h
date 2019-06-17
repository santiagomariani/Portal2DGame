
#ifndef MUSICA_H
#define MUSICA_H

#include <string>
#include <SDL2/SDL_mixer.h>

class Musica {
private:
    Mix_Music *musica;
public:
    // Carga la musica.
    Musica(std::string nombre_archivo);
    // Reproduce la musica una vez.
    void reproducirUnaVez();
    // Reproduce la musica en loop (vuelva a iniciar luego de terminada).
    void reproducirEnLoop();
    // Setea el volumen de la musica.
    void setearVolumen(uint8_t volumen);
    // Resume la musica.
    void despausar();
    // Pausa la musica.
    void pausar();
    // Para la musica.
    void parar();
    // Devuelve booleano indicando si se esta reproduciendo la musica.
    bool seEstaReproduciendo();
    // Libera la musica.
    ~Musica();

};


#endif //MUSICA_H
