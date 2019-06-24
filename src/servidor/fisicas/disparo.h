#ifndef DISPARO_H
#define DISPARO_H

#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"
#include "portal.h"

class Disparo : public Cuerpo{
    int id;
    Mundo& mundo;
    b2Body* cuerpo;
    Portal* portal;

public:
    Disparo(int identidad, Mundo& mundo);
    // Se crea el disparo en la posicion origen con una velocidad con
    // direccion dada por V = Vdestino - Vorigen.
    void activar(const b2Vec2& origen, const b2Vec2& destino);
    Disparo(Disparo&& otro);
    void setPortal(Portal* port);
    // Se destruye el disparo.
    void desactivar();
    Disparo& operator=(Disparo&& otro);
    // Devuelve la posicion del disparo.
    const b2Vec2& getPosition();
    // Devuelve el angulo del disparo.
    int32_t getAngle() override;
    // Devuelve el Id asociado con Disparo.
    uint8_t getId();
    void empezarContacto(Cuerpo* otro);
    void crearPortal(b2Vec2& pos, b2Vec2& normal);
    // Agrega el cuerpo a destruir luego de un choque.
    void terminar();
};

#endif //DISPARO_H
