#ifndef RECEPTOR_H
#define RECEPTOR_H

#include "cuerpo.h"
#include "mundo.h"
#include "sensor_receptor.h"

class SensorReceptor;

// Representa el receptor de las Bolas de Energia.
// Pueden activarse cuando les llega una bola de energia.
// Hay varios tipos de receptores, segun de donde recibe la bola de energia:
// Abajo, arriba, derecha, izquierda.

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
    // Activa el receptor.
    void activar();
    bool estaActivado() override;
    virtual ~Receptor();
};


#endif //RECEPTOR_H
