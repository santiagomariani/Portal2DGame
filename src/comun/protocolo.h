
#ifndef PROTOCOLO_H
#define PROTOCOLO_H


#include <deque>
#include <info_cuerpo_box_2_d.h>

#include "estado_teclado.h"
#include "cuerpo.h"
#include "info_cuerpo.h"
#include "convertidor_coordenadas.h"
#include "input.h"
#include "Skt.h"
#include "mensajero.h"

#define MSJ_INPUT 1
#define MSJ_CUERPO 2
#define MSJ_FINALIZO_FOTOGRAMA 3
#define MSJ_OPCION_NUEVA_PARTIDA 4
#define MSJ_PARTIDA_CREADA 5
#define MSJ_OPCION_UNIRSE_PARTIDA 6

class Protocolo {
private:
    Mensajero &mensajero;

public:
    explicit Protocolo(Mensajero &mensajero);
    // Envia el input (estado de mouse y teclado) y el id de la Chell asociada
    // con ese Input.
    void enviarInput(Input &input);
    // Envia la informacion de interes de un cuerpo.
    void enviarCuerpo(InfoCuerpoBox2D &info_cuerpo);
    // Envia un mensaje indicando que finalizo el fotograma.
    // Se reciben muchos cuerpos (la informacion de estos en realidad), y es
    // necesario saber cual es el ultimo (para saber cuando renderizar todo
    // junto).
    void enviarFinalizoFotograma();
    // Se recibe el input (estado de mouse y teclado) y el id de la Chell
    // asociada con ese input.
    Input recibirInput();
    // Se recibe la informacion de un cuerpo en la estructura InfoCuerpo.
    void recibirCuerpo(InfoCuerpo &info_cuerpo,
            ConvertidorCoordenadas &convertidor_coordenadas);
    // Recibe un codigo de mensaje. El mismo se utiliza despues para saber
    // que es lo que se recibe y llamar al metodo correcto.
    uint8_t recibirCodigoMensaje();
    // Envia el id del jugador.
    void enviarId(uint32_t id);
    // Recibe el id del jugador.
    uint32_t recibirId();
    // Envia opcion nueva partida.
    void enviarOpcionNuevaPartida();
    // Envia opcion unirse a partida.
    void enviarOpcionUnirsePartida();
    // Envia el puerto.
    void enviarPuerto(std::string port);
    // Recibe el puerto.
    std::string recibirPuerto();
    // Envia mensaje al cliente indicando que la partida fue creada.
    void enviarPartidaCreada();
};


#endif //PROTOCOLO_H
