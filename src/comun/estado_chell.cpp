
#include <iostream>
#include "estado_chell.h"

EstadoChell::EstadoChell() : estado_actual(CHELL_QUIETA),
    orientacion_actual(CHELL_MIRA_DERECHA), disparo(false) {
}

EstadoChell::EstadoChell(EstadoChell &&otro) {
    estado_actual = otro.estado_actual;
    orientacion_actual = otro.orientacion_actual;
    disparo = otro.disparo;
    otro.disparo = false;
}

// Borrar | Solo para probar que funcionen todos los sonidos.
int i = 0;

void EstadoChell::actualizarEstado(SensorChell &s, b2Vec2 &vel) {

    uint8_t orientacion_nueva;
    uint8_t estado_nuevo;

    if (estado_actual == CHELL_GANO){
        return;
    }
    
    // hardcodeado - ver que hacer desp con la muerte.
    if ((estado_actual == CHELL_MUERE) && (i == 0)) {
        ++i;
        return;
    }
    
    if (vel.x > 0) {
        orientacion_nueva = CHELL_MIRA_DERECHA;
    } else if (vel.x < 0) {
        orientacion_nueva = CHELL_MIRA_IZQ;
    } else {
        orientacion_nueva = orientacion_actual;
    }

    if (s.estaActivado() && orientacion_nueva != orientacion_actual) {
        estado_nuevo = CHELL_CAMBIA_ORIENTACION;
    } else if (s.estaActivado() && (abs(vel.x) == 0)) {
        if (disparo) {
            estado_nuevo = CHELL_QUIETA_Y_DISPARA;
        } else {
            estado_nuevo = CHELL_QUIETA;
        }
    } else if (s.estaActivado() && (abs(vel.x)) > 0) {
        if (disparo) {
            estado_nuevo = CHELL_MOVIENDOSE_Y_DISPARA;
        } else {
            estado_nuevo = CHELL_MOVIENDOSE;
        }
    } else if (!s.estaActivado()) {
        if (disparo) {
            estado_nuevo = CHELL_EN_EL_AIRE_Y_DISPARA;
        } else if ((estado_actual != CHELL_EN_EL_AIRE_Y_DISPARA)
            && (estado_actual != CHELL_EN_EL_AIRE)
            && (estado_actual != CHELL_SALTA)) {
            estado_nuevo = CHELL_SALTA;
        } else {
            estado_nuevo = CHELL_EN_EL_AIRE;
        }
    } else {
        estado_nuevo = estado_actual;
    }
    estado_actual = estado_nuevo;
    orientacion_actual = orientacion_nueva;
    disparo = false;
}

void EstadoChell::ocurrioDisparo() {
    disparo = true;
}

uint8_t EstadoChell::obtenerEstado() {
    return estado_actual;
}

uint8_t EstadoChell::obtenerOrientacion() {
    return orientacion_actual;
}

void EstadoChell::chellMurio() {
    estado_actual = CHELL_MUERE;
}

void EstadoChell::chellGano() {
    estado_actual = CHELL_GANO;
}
