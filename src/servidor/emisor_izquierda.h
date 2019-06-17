
#include "mundo.h"
#include "bola_energia.h"
#include "emisor.h"

#ifndef EMISORIZQUIERDA_H
#define EMISORIZQUIERDA_H


class EmisorIzquierda : public Emisor {
public:
    EmisorIzquierda(Mundo &mundo, const b2Vec2 &pos);
    EmisorIzquierda(EmisorIzquierda &&otro);
    EmisorIzquierda& operator=(EmisorIzquierda &&otro);
    uint8_t getId() override;
};


#endif //EMISORIZQUIERDA_H
