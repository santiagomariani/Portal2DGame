
#ifndef ESTADO_CHELL_H
#define ESTADO_CHELL_H

#include "sensor_chell.h"
#include "estado_teclado.h"

#define CHELL_EN_EL_AIRE 0
#define CHELL_MOVIENDOSE 1
#define CHELL_QUIETA 2
#define CHELL_CAMBIA_ORIENTACION 3
#define CHELL_MOVIENDOSE_Y_DISPARA 4
#define CHELL_QUIETA_Y_DISPARA 5
#define CHELL_EN_EL_AIRE_Y_DISPARA 6
#define CHELL_SALTA 7
#define CHELL_MUERE 8
#define CHELL_GANO 10

#define CHELL_MIRA_DERECHA 0
#define CHELL_MIRA_IZQ 1

class EstadoChell {
private:
    uint8_t estado_actual;
    uint8_t orientacion_actual;
    bool disparo;

public:
    EstadoChell();
    EstadoChell(EstadoChell &&otro);
    // Se actualiza el estado actual de la Chell.
    void actualizarEstado(SensorChell &s, b2Vec2 &vel);
    // Se notifica que ocurrio un disparo. Esto se tiene en cuenta luego para
    // poder cambiar el estado actual de la Chell de manera correcta.
    void ocurrioDisparo();
    // Devuelve el estado actual de la Chell.
    uint8_t obtenerEstado();
    // Devuelve la orientacion actual de la Chell.
    uint8_t obtenerOrientacion();
    // Actualiza el estado de la Chell por haber muerto.
    void chellMurio();
    // Actualiza el estado de la Chell por haber llegado a la torta.
    void chellGano();
};


#endif //ESTADO_CHELL_H
