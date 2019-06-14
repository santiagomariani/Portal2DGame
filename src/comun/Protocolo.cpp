//
// Created by santi on 08/06/19.
//

#include <netinet/in.h>
#include "Protocolo.h"
#include "ids.h"
#include "chell.h"
#include "CoordConverter.h"



Protocolo::Protocolo(Mensajero &mensajero) :
    mensajero(mensajero) {
}

void Protocolo::enviarInput(Input &input) {
    /*
     *  1 - Mando codigo de mensaje: uint8_t
     *  2 - Mando id de la chell: uint32_t
     *  3 - Se manda cantidad de teclas: uint8_t
     *  4 - Se manda la tecla y si esta presionado o no:
     *         tecla: sint32
     *         estado tecla: uint8_t
     *  5 - Mando estado de mouse.
     */

    // Codigo de mensaje
    uint8_t codigo_mensaje = MSJ_INPUT;
    mensajero << codigo_mensaje;

    // Id de Chell
    uint32_t id = input.id;
    mensajero << id;


    auto mapa_teclado = input.estado_teclado.obtenerMapa();

    // Cantidad de teclas.
    uint8_t cant_teclas = mapa_teclado.size();
    mensajero << cant_teclas;

    for (auto it = mapa_teclado.begin(); it != mapa_teclado.end(); it++) {
        // SDL_Keycode
        int32_t key_code = it->first;
        // Estado tecla.
        uint8_t estado_tecla = it->second;

        mensajero << key_code << estado_tecla;
    }

    EstadoMouse &estado_mouse = input.estado_mouse;
    uint8_t click_derecho;
    uint8_t click_izquierdo;

    // Mando click derecho.
    if (estado_mouse.clickDerecho()) {
        click_derecho = 1;
        b2Vec2 pos = estado_mouse.posClickDerecho();
        mensajero << click_derecho << pos.x << pos.y;
    } else {
        click_derecho = 0;
        mensajero << click_derecho;
    }

    // Mando click izquierdo.
    if (estado_mouse.clickIzquierdo()) {
        click_izquierdo = 1;
        b2Vec2 pos = estado_mouse.posClickIzquierdo();
        mensajero << click_izquierdo << pos.x << pos.y;
    } else {
        click_izquierdo = 0;
        mensajero << click_izquierdo;
    }
}

Input Protocolo::recibirInput() {
    Input input;
    uint32_t id;
    mensajero >> id;
    input.id = id;

    uint8_t cant_teclas;
    mensajero >> cant_teclas;
    for (int i = 0; i < cant_teclas; ++i) {
        int32_t key_code;
        uint8_t estado_tecla;
        mensajero >> key_code >> estado_tecla;
        SDL_KeyboardEvent event;
        event.keysym.sym = key_code;
        event.state = estado_tecla;
        input.estado_teclado.agregar_evento(event);
    }
    uint8_t click_derecho;
    uint8_t click_izquierdo;

    mensajero >> click_derecho;
    if (click_derecho) {
        b2Vec2 pos_click;
        mensajero >> pos_click.x >> pos_click.y;
        input.estado_mouse.agregarClickDerecho(pos_click);
    }
    mensajero >> click_izquierdo;
    if (click_izquierdo) {
        b2Vec2 pos_click;
        mensajero >> pos_click.x >> pos_click.y;
        input.estado_mouse.agregarClickIzquierdo(pos_click);
    }
    return input;
}

void Protocolo::enviarCuerpo(InfoCuerpoBox2D &info_cuerpo) {
    /*
    codigo mensaje: uint8_t
    id: uint8_t
    estado: uint8_t
    orientacion: uint8_t
    angulo: int32_t
    x: float32
    y: float32
    ancho maximo: float32
    alto maximo: float32
    id_chell: uint8_t
    */

    uint8_t codigo_mensaje = MSJ_CUERPO;
    mensajero << codigo_mensaje;

    uint8_t id =  info_cuerpo.id;
    uint8_t estado = info_cuerpo.estado;
    uint8_t orientacion = info_cuerpo.orientacion;
    int32_t angulo = info_cuerpo.angulo;
    b2Vec2 pos_cuerpo = info_cuerpo.pos;
    float32 x = pos_cuerpo.x;
    float32 y = pos_cuerpo.y;
    float32 ancho_maximo = info_cuerpo.ancho;
    float32 alto_maximo = info_cuerpo.alto;
    uint8_t id_chell = info_cuerpo.id_chell;

    mensajero << id << estado << orientacion;
    mensajero << angulo;
    mensajero << x << y << ancho_maximo << alto_maximo;
    mensajero << id_chell;
}

void Protocolo::recibirCuerpo(InfoCuerpo &info_cuerpo, CoordConverter &coord_converter) {
    uint8_t orientacion;
    b2Vec2 pos_cuerpo;
    float32 ancho_maximo;
    float32 alto_maximo;
    
    mensajero >> info_cuerpo.id >> info_cuerpo.estado >> orientacion;
    mensajero >> info_cuerpo.angulo >> pos_cuerpo.x >> pos_cuerpo.y;
    mensajero >> ancho_maximo >> alto_maximo;
    mensajero >> info_cuerpo.id_chell;

    info_cuerpo.dest = coord_converter.box2DToSDL(pos_cuerpo,
            ancho_maximo,
            alto_maximo);
    if (info_cuerpo.id == ID_CHELL) {
        if (orientacion == CHELL_MIRA_DERECHA) {
            if (info_cuerpo.estado == CHELL_CAMBIA_ORIENTACION) {
                info_cuerpo.flip = SDL_FLIP_HORIZONTAL;
            } else {
                info_cuerpo.flip = SDL_FLIP_NONE;
            }
        } else {
            if (info_cuerpo.estado == CHELL_CAMBIA_ORIENTACION) {
                info_cuerpo.flip = SDL_FLIP_NONE;
            } else {
                info_cuerpo.flip = SDL_FLIP_HORIZONTAL;
            }
        }
    } else {
        info_cuerpo.flip = SDL_FLIP_NONE;
    }
}

void Protocolo::enviarFinalizoFotograma() {
    uint8_t codigo_mensaje = MSJ_FINALIZO_FOTOGRAMA;
    mensajero << codigo_mensaje;
}

uint8_t Protocolo::recibirCodigoMensaje() {
    uint8_t codigo_mensaje;
    mensajero >> codigo_mensaje;
    return codigo_mensaje;
}

void Protocolo::enviarId(uint32_t id) {
    mensajero << id;
}

uint32_t Protocolo::recibirId() {
    uint32_t id;
    mensajero >> id;
    return id;
}

void Protocolo::enviarOpcionNuevaPartida() {
    uint8_t codigo_mensaje = MSJ_OPCION_NUEVA_PARTIDA;
    mensajero << codigo_mensaje;

}

void Protocolo::enviarPuerto(std::string puerto) {
    mensajero << puerto;
}

std::string Protocolo::recibirPuerto() {
    std::string puerto;
    mensajero >> puerto;
    return puerto;
}

void Protocolo::enviarPartidaCreada() {
    uint8_t codigo_mensaje = MSJ_PARTIDA_CREADA;
    mensajero << codigo_mensaje;
}

void Protocolo::enviarOpcionUnirsePartida() {
    uint8_t codigo_mensaje = MSJ_OPCION_UNIRSE_PARTIDA;
    mensajero << codigo_mensaje;
}
