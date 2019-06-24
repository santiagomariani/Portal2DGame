#include "sensor_receptor.h"
#include "ids.h"
#include "bola_energia.h"

SensorReceptor::SensorReceptor(Receptor &receptor) : receptor(receptor) {
}

void SensorReceptor::empezarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_BOLAENERGIA) {
        receptor.activar();
        ((BolaEnergia*)otro)->agregarCuerpoADestruir();
    }
}

void SensorReceptor::terminarContacto(Cuerpo *otro) {
}
