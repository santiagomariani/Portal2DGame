#include "estado_teclado.h"

EstadoTeclado::EstadoTeclado(){
}

void EstadoTeclado::agregar_evento(int tecla, uint8_t estado) {
    estado_tecla[tecla] = estado;
}

bool EstadoTeclado::presionada(int tecla) {
    return (estado_tecla[tecla] == 1);
}

bool EstadoTeclado::liberada(int tecla) {
    return (estado_tecla[tecla] == 0);
}

std::map<int, uint8_t> &EstadoTeclado::obtenerMapa(){
    return estado_tecla;
}

