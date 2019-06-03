//
// Created by santi on 01/06/19.
//

#ifndef EMISOR_H
#define EMISOR_H


#include "mundo.h"
#include "BolaEnergia.h"

#define TAMANIO_EMISOR 0.5f

class Emisor : public Cuerpo {
protected:
    const unsigned int FRECUENCIA = 300;
    unsigned int contador;
    b2Body *cuerpo;
    std::vector<std::unique_ptr<BolaEnergia>> bolas_energia;
    Mundo &mundo;
    b2Vec2 pos_creacion;
    b2Vec2 dir_vel;
public:
    Emisor(Mundo &mundo, const b2Vec2 &pos);
    explicit Emisor(Mundo &mundo);
    void actualizar() override;
    const b2Vec2& getPosition() override;
    void emitirBolaEnergia();
    void empezarContacto(Cuerpo *otro) override;
    void terminarContacto(Cuerpo *otro) override;
    b2Body* getBody() override;
};


#endif //EMISOR_H
