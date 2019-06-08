//
// Created by santi on 08/06/19.
//

#ifndef PROTOCOLO_H
#define PROTOCOLO_H


#include <deque>
#include "estado_teclado.h"
#include "cuerpo.h"
#include "InfoCuerpo.h"
#include "CoordConverter.h"

class Protocolo {
private:
    char input_serializado[500];
    char cuerpo_serializado[500];
    CoordConverter &coord_converter;
public:
    explicit Protocolo(CoordConverter &coord_converter);
    void enviarTeclado(EstadoTeclado &estado_teclado);
    void recibirTeclado(EstadoTeclado &estado_teclado);
    void enviarCuerpo(Cuerpo &cuerpo);
    void recibirCuerpo(InfoCuerpo &info_cuerpo);
};


#endif //PROTOCOLO_H
