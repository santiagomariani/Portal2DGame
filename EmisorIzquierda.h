//
// Created by santi on 31/05/19.
//

#include "mundo.h"
#include "BolaEnergia.h"
#include "Emisor.h"

#ifndef EMISORIZQUIERDA_H
#define EMISORIZQUIERDA_H


class EmisorIzquierda : public Emisor {
public:
    EmisorIzquierda(Mundo &mundo, const b2Vec2 &pos);
    EmisorIzquierda(EmisorIzquierda &&otro);
    EmisorIzquierda& operator=(EmisorIzquierda &&otro);
    int getId() override;
};


#endif //EMISORIZQUIERDA_H
