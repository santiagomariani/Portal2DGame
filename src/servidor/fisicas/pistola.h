#ifndef PISTOLA_H
#define PISTOLA_H

#include "portal.h"
#include "disparo.h"

// Clase que se encarga
// de disparar y conectar los portales azul y naranja
// de una misma pistola. Haciendo que siempre haya un solo portal
// Azul y uno naranja.

class Pistola{
    Mundo& mundo;
    Disparo d_azul;
    Disparo d_naranja;
    Portal p_azul;
    Portal p_naranja;

public:
    Pistola(Mundo& mundo);
    Pistola(Pistola&& otro);
    void dispararAzul(const b2Vec2& origen, const b2Vec2& destino);
    void dispararNaranja(const b2Vec2& origen, const b2Vec2& destino);
};

#endif 