//
// Created by santi on 08/06/19.
//

#ifndef PROTOCOLO_H
#define PROTOCOLO_H


#include <deque>
#include <info_cuerpo_box_2_d.h>

#include "estado_teclado.h"
#include "cuerpo.h"
#include "InfoCuerpo.h"
#include "CoordConverter.h"
#include "Input.h"
#include "Skt.h"
#include "Mensajero.h"

#define MSJ_INPUT 1
#define MSJ_CUERPO 2
#define MSJ_FINALIZO_FOTOGRAMA 3
#define MSJ_OPCION_NUEVA_PARTIDA 4
#define MSJ_PARTIDA_CREADA 5
#define MSJ_OPCION_UNIRSE_PARTIDA 6
#define MSJ_CHELL_MUERTA 7

class Protocolo {
private:
    Mensajero &mensajero;
public:
    explicit Protocolo(Mensajero &mensajero);
    void enviarInput(Input &input);
    void enviarCuerpo(InfoCuerpoBox2D &info_cuerpo);
    void enviarFinalizoFotograma();
    Input recibirInput();
    void recibirCuerpo(InfoCuerpo &info_cuerpo,
            CoordConverter &coord_converter);
    uint8_t recibirCodigoMensaje();
    void enviarId(uint8_t id);
    uint8_t recibirId();

    void enviarChellMuerta(uint8_t id);

    void enviarOpcionNuevaPartida();

    void enviarOpcionUnirsePartida();

    void enviarPuerto(std::string basicString);

    void enviarCantidad(uint16_t cant);

    uint16_t recibirCantidad();

    std::string recibirPuerto();

    void enviarPartidaCreada();
};


#endif //PROTOCOLO_H
