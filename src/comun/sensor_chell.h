
#ifndef SENSOR_CHELL_H
#define SENSOR_CHELL_H


#include "sensor.h"

class SensorChell : public Sensor {
private:
    bool activado;
    int cant_contactos;
    // Actualiza el estado del sensor. Si la cantidad de contactos es 0,
    // entonces el sensor esta desactivado. En otro caso esta activado.
    void actualizarEstadoSensor();

public:
    SensorChell();
    // Devuelve un booleano indicando si esta activado el sensor.
    bool estaActivado();
    // Al empezar contacto con un cuerpo se incrementa la cantidad de
    // contactos. Luego se actualiza el estado del sensor en base a esta
    // cantidad.
    void empezarContacto(Cuerpo* otro) override;
    // Al terminar contacto con un cuerpo se decrementa la cantidad de
    // contactos. Luego se actualiza el estado del sensor en base a esta
    // cantidad.
    void terminarContacto(Cuerpo* otro) override;
};


#endif //SENSOR_CHELL_H
