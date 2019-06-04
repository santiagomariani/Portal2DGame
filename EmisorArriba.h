//
// Created by santi on 31/05/19.
//

#ifndef EMISORARRIBA_H
#define EMISORARRIBA_H


#include "mundo.h"
#include "BolaEnergia.h"
#include "Emisor.h"

#define TAMANIO_EMISOR 0.5f

class EmisorArriba : public Emisor {
public:
    EmisorArriba(Mundo &mundo, const b2Vec2 &pos);
    EmisorArriba(EmisorArriba &&otro);
    EmisorArriba& operator=(EmisorArriba &&otro);
    int getId() override;
};


#endif //EMISORARRIBA_H
