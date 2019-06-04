//
// Created by santi on 02/06/19.
//

#include "ReceptorAbajo.h"
#include "Receptor.h"
#include "ids.h"

ReceptorAbajo::ReceptorAbajo(Mundo &mundo, const b2Vec2 &pos) :
        Receptor(mundo ,pos) {
    b2Vec2 pos_sensor(0, (float32)(- (maxHeight / 2) - TAMANIO_SENSOR_Y));
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.userData = sensor.get();
    polygon_shape.SetAsBox(TAMANIO_SENSOR_X, TAMANIO_SENSOR_Y, pos_sensor, 0);
    cuerpo->CreateFixture(&fixture_def);
}

int ReceptorAbajo::getId() {
    if (activado) {
        return ID_RECEPTORABAJO_ACTIVADO;
    } else {
        return ID_RECEPTORABAJO_DESACTIVADO;
    }
}