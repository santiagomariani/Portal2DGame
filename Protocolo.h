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
#include "Input.h"
#include "Skt.h"
#include "Mensajero.h"

class Protocolo {
private:
    Mensajero &mensajero;
public:
    explicit Protocolo(Mensajero &mensajero);
    void enviarInput(Input &input);
    void recibirInput(Input &input);
    void enviarCuerpo(Cuerpo &cuerpo);
    void recibirCuerpo(InfoCuerpo &info_cuerpo,
            CoordConverter &coord_converter);
};


#endif //PROTOCOLO_H
