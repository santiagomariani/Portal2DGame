#include <config.h>
#include "receptor_izquierda.h"
#include "receptor.h"
#include "ids.h"

ReceptorIzquierda::ReceptorIzquierda(Mundo &mundo, const b2Vec2 &pos) :
        Receptor(mundo ,pos) {
    b2Vec2 pos_sensor((float32)(- (maxWidth / 2) - TAMANIO_SENSOR_X), 0);
    b2PolygonShape polygon_shape;
    b2FixtureDef fixture_def;
    fixture_def.shape = &polygon_shape;
    fixture_def.userData = sensor.get();
    polygon_shape.SetAsBox(TAMANIO_SENSOR_X, config.tam_receptor, pos_sensor, 0);
    cuerpo->CreateFixture(&fixture_def);
}

uint8_t ReceptorIzquierda::getId() {
    if (activado) {
        return ID_RECEPTORIZQUIERDA_ACTIVADO;
    } else {
        return ID_RECEPTORIZQUIERDA_DESACTIVADO;
    }
}
