#include "SensorReceptor.h"
#include "ids.h"
#include "BolaEnergia.h"

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
