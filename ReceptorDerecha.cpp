//
// Created by santi on 02/06/19.
//

#include "ReceptorDerecha.h"
#include "Receptor.h"
#include "ids.h"

ReceptorDerecha::ReceptorDerecha(Mundo &mundo, const b2Vec2 &pos) :
        Receptor(mundo ,pos) {
    b2Vec2 pos_sensor((float32)((maxWidth / 2) + TAMANIO_SENSOR_X), 0);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.userData = sensor.get();
    polygon_shape.SetAsBox(TAMANIO_SENSOR_X, TAMANIO_SENSOR_Y, pos_sensor, 0);
    cuerpo->CreateFixture(&fixture_def);
}

uint8_t ReceptorDerecha::getId() {
    if (activado) {
        return ID_RECEPTORDERECHA_ACTIVADO;
    } else {
        return ID_RECEPTORDERECHA_DESACTIVADO;
    }
}
