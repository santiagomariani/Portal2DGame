//
// Created by santi on 08/06/19.
//

#ifndef PROTOCOLO_H
#define PROTOCOLO_H


#include <deque>

#include "estado_teclado.h"
#include "cuerpo.h"
#include "info_cuerpo.h"
#include "convertidor_coordenadas.h"
#include "input.h"
#include "skt.h"
#include "mensajero.h"

#define MSJ_INPUT 1
#define MSJ_CUERPO 2
#define MSJ_FINALIZO_FOTOGRAMA 3

class Protocolo {
private:
    Mensajero &mensajero;
public:
    explicit Protocolo(Mensajero &mensajero);
    void enviarInput(Input &input);
    void enviarCuerpo(Cuerpo &cuerpo);
    void enviarFinalizoFotograma();
    void recibirInput(Input &input);
    void recibirCuerpo(InfoCuerpo &info_cuerpo,
            CoordConverter &coord_converter);
    uint8_t recibirCodigoMensaje();
};


#endif //PROTOCOLO_H
