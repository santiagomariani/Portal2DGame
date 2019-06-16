#ifndef EMISOR_H
#define EMISOR_H

#include "mundo.h"
#include "BolaEnergia.h"

// Emisor de bolas de energia.
// Hay cuatro tipos de emisores segun para donde emiten las bolas de energia:
// Derecha, Izquierda, Arriba, Abajo

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
    // Actualiza el emisor para ver si debe emitir una bola de energia
    void actualizar() override;
    const b2Vec2& getPosition() override;
    void emitirBolaEnergia();
    void empezarContacto(Cuerpo *otro) override;
    void terminarContacto(Cuerpo *otro) override;
    b2Body* getBody() override;
};


#endif //EMISOR_H
