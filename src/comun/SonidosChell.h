//
// Created by santi on 14/06/19.
//

#ifndef SONIDOSCHELL_H
#define SONIDOSCHELL_H


#include <cstdint>
#include <map>
#include "Sonido.h"

class SonidosChell {
private:
    std::map<uint8_t, Sonido> sonidos;
    void creacionSonidos();
    bool dispara(uint8_t estado);
public:
    SonidosChell();
    void reproducir(uint8_t estado);
};


#endif //SONIDOSCHELL_H
