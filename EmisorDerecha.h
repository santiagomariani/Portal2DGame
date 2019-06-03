//
// Created by santi on 31/05/19.
//

#include "mundo.h"
#include "BolaEnergia.h"
#include "Emisor.h"

#ifndef EMISORDERECHA_H
#define EMISORDERECHA_H


class EmisorDerecha : public Emisor {
public:
    EmisorDerecha(Mundo &mundo, const b2Vec2 &pos);
    EmisorDerecha(EmisorDerecha &&otro);
    EmisorDerecha& operator=(EmisorDerecha &&otro);
    int getId() override;
};


#endif //EMISORDERECHA_H
