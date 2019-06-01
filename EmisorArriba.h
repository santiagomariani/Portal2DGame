//
// Created by santi on 31/05/19.
//

#ifndef EMISORARRIBA_H
#define EMISORARRIBA_H


#include "mundo.h"
#include "BolaEnergia.h"

#define TAMANIO_EMISOR 0.5f

class EmisorArriba : public Cuerpo {
private:
    const unsigned int FRECUENCIA = 100;
    unsigned int contador;
    b2Body *cuerpo;
    std::vector<BolaEnergia> bolas_energia;
    Mundo &mundo;
public:
    EmisorArriba(Mundo &mundo, const b2Vec2 &pos);
    EmisorArriba(EmisorArriba &&otro);
    EmisorArriba& operator=(EmisorArriba &otro);
    EmisorArriba& operator=(EmisorArriba &&otro);
    int getId() override;
    void actualizar() override;
    const b2Vec2& getPosition() override;
    void emitirBolaEnergia();
    void empezarContacto(Cuerpo *otro);
    void terminarContacto(Cuerpo *otro);
    b2Body* getBody() override;
};


#endif //EMISORARRIBA_H
