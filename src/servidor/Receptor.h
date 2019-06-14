//
// Created by santi on 02/06/19.
//

#ifndef RECEPTOR_H
#define RECEPTOR_H


#include "cuerpo.h"
#include "mundo.h"
#include "SensorReceptor.h"

#define TAMANIO_RECEPTOR 0.5f
class SensorReceptor;
class Receptor : public Cuerpo {
protected:
    bool activado;
    b2Body *cuerpo;
    std::unique_ptr<SensorReceptor> sensor;
public:
    Receptor(Mundo &mundo, const b2Vec2 &pos);
    const b2Vec2& getPosition() override;
    void empezarContacto(Cuerpo *otro) override;
    void terminarContacto(Cuerpo *otro) override;
    b2Body* getBody() override;
    void activar();
    bool estaActivado() override;
    virtual ~Receptor();
};


#endif //RECEPTOR_H
