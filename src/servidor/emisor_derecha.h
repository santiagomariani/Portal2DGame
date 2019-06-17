
#include "mundo.h"
#include "bola_energia.h"
#include "emisor.h"

#ifndef EMISORDERECHA_H
#define EMISORDERECHA_H

class EmisorDerecha : public Emisor {
public:
    EmisorDerecha(Mundo &mundo, const b2Vec2 &pos);
    EmisorDerecha(EmisorDerecha &&otro);
    EmisorDerecha& operator=(EmisorDerecha &&otro);
    uint8_t getId() override;
};


#endif //EMISORDERECHA_H
