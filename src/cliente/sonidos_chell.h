
#ifndef SONIDOS_CHELL_H
#define SONIDOS_CHELL_H


#include <cstdint>
#include <map>
#include "sonido.h"

class SonidosChell {
private:
    // Mapa de estados y sonidos.
    std::map<uint8_t, Sonido> sonidos;
    // Crea todos los sonidos y los asocia con un estado.
    void creacionSonidos();
    // Devuelve un booleano indicando si el estado representa un disparo.
    bool dispara(uint8_t estado);

public:
    SonidosChell();
    // Reproduce el sonido de Chell asociado con el estado recibido (si
    // el estado tuviese un sonido asociado).
    void reproducir(uint8_t estado);
};


#endif //SONIDOS_CHELL_H
