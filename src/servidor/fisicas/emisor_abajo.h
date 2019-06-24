
#include "mundo.h"
#include "bola_energia.h"
#include "emisor.h"

#ifndef EMISORABAJO_H
#define EMISORABAJO_H


class EmisorAbajo : public Emisor {
public:
    EmisorAbajo(Mundo &mundo, const b2Vec2 &pos);
    EmisorAbajo(EmisorAbajo &&otro);
    EmisorAbajo& operator=(EmisorAbajo &&otro);
    uint8_t getId() override;
};


#endif //EMISORABAJO_H
