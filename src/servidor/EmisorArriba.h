
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
    uint8_t getId() override;
};


#endif //EMISORARRIBA_H
