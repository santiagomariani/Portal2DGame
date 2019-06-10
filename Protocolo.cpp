//
// Created by santi on 08/06/19.
//

#include <netinet/in.h>
#include "Protocolo.h"
#include "ids.h"
#include "chell.h"
#include "BolaEnergia.h"
#include "CoordConverter.h"

#define INPUT 1
#define CUERPO 2

Protocolo::Protocolo(CoordConverter &coord_converter,
        Mensajero &mensajero) :
    coord_converter(coord_converter),
    mensajero(mensajero) {
}

void Protocolo::enviarInput(Input &input) {
    /*
     *  1 - Mando codigo de mensaje.
     *  2 - Se manda cantidad de teclas: uint8_t
     *  3 - Se manda la tecla y si esta presionado o no:
     *         tecla: sint32
     *         estado tecla: uint8_t
     *  4 - Mando estado de mouse.
     */

    // Codigo de mensaje
    uint8_t codigo_mensaje = INPUT;
    mensajero << codigo_mensaje;

    auto mapa_teclado = input.estado_teclado.obtenerMapa();
    // Cantidad de teclas.
    uint8_t cant_teclas = mapa_teclado.size();
    mensajero << cant_teclas;

    for (auto it = mapa_teclado.begin(); it != mapa_teclado.end(); it++) {
        // SDL_Keycode -> sint32
        Sint32 key_code = it->first;
        mensajero << key_code;
        // Estado tecla.
        uint8_t estado_tecla = it->second;
        mensajero << estado_tecla;
    }

    EstadoMouse &estado_mouse = input.estado_mouse;
    uint8_t click_derecho;
    uint8_t click_izquierdo;

    // Mando click derecho.
    if (estado_mouse.clickDerecho()) {
        click_derecho = 1;
        mensajero << click_derecho;
        b2Vec2 pos = estado_mouse.posClickDerecho();
        mensajero << pos.x;
        mensajero << pos.y;
    } else {
        click_derecho = 0;
        mensajero << click_derecho;
    }

    // Mando click izquierdo.
    if (estado_mouse.clickIzquierdo()) {
        click_izquierdo = 1;
        mensajero << click_izquierdo;
        b2Vec2 pos = estado_mouse.posClickIzquierdo();
        mensajero << pos.x;
        mensajero << pos.y;
    } else {
        click_izquierdo = 0;
        mensajero << click_izquierdo;
    }
}

void Protocolo::recibirInput(Input &input) {
    // Cantidad de teclas

    /*
    uint8_t cant_teclas;
    ((char*)(&cant_teclas))[0] = input_serializado[0];

    for (int i = 0, j = 1; i < cant_teclas; ++i) {
        // Leo SDL_Keycode -> sint32.
        Sint32 key_code;
        for (int k = 0; k < 4; ++k) {
            ((char*)(&key_code))[k] = input_serializado[j];
            ++j;
        }
        key_code = ntohl(key_code);
        uint8_t tecla_presionada;
        ((char*)(&tecla_presionada))[0] = input_serializado[j];
        ++j;
        SDL_KeyboardEvent event;
        event.keysym.sym = key_code;
        event.state = tecla_presionada;
        estado_teclado.agregar_evento(event);
    }
    */
}

void Protocolo::enviarCuerpo(Cuerpo &cuerpo) {
    /*
    uint8_t id;
    uint8_t estado;
    uint8_t orientacion;
    int32_t angulo;
    SDL_Rect dest;
    //int x int y int w int h
     */
    uint8_t id =  cuerpo.getId();
    uint8_t estado;
    uint8_t orientacion;
    if (id == ID_CHELL) {
        estado = ((Chell*)&cuerpo)->obtenerEstado();
        orientacion = ((Chell*)&cuerpo)->obtenerOrientacion();
    } else {
        estado = 0;
        orientacion = 0;
    }
    int32_t angulo = cuerpo.getAngle();
    SDL_Rect dest = coord_converter.box2DToSDL(cuerpo);

    int j = 0;
    // Mando id.
    cuerpo_serializado[j] = ((char*)(&id))[0];
    ++j;
    // Mando estado.
    cuerpo_serializado[j] = ((char*)(&estado))[0];
    ++j;
    // Mando orientacion
    cuerpo_serializado[j] = ((char*)(&orientacion))[0];
    ++j;

    // Mando angulo
    angulo = htonl(angulo);
    for (int i = 0; i < 4; ++i) {
        cuerpo_serializado[j] = ((char*)(&angulo))[i];
        ++j;
    }

    // Mando x
    dest.x = htonl(dest.x);
    for (int i = 0; i < 4; ++i) {
        cuerpo_serializado[j] = ((char*)(&dest.x))[i];
        ++j;
    }

    // Mando y
    dest.y = htonl(dest.y);
    for (int i = 0; i < 4; ++i) {
        cuerpo_serializado[j] = ((char*)(&dest.y))[i];
        ++j;
    }

    // Mando w
    dest.w = htonl(dest.w);
    for (int i = 0; i < 4; ++i) {
        cuerpo_serializado[j] = ((char*)(&dest.w))[i];
        ++j;
    }

    // Mando h
    dest.h = htonl(dest.h);
    for (int i = 0; i < 4; ++i) {
        cuerpo_serializado[j] = ((char*)(&dest.h))[i];
        ++j;
    }

}

void Protocolo::recibirCuerpo(InfoCuerpo &info_cuerpo) {
    int j = 0;

    uint8_t id, estado, orientacion;
    int32_t angulo;
    SDL_Rect dest;

    // Recibo id.
    ((char*)(&id))[0] = input_serializado[j];
    ++j;
    // Recibo estado.
    ((char*)(&estado))[0] = input_serializado[j];
    ++j;
    // Recibo orientacion.
    ((char*)(&orientacion))[0] = input_serializado[j];
    ++j;
    // Recibo angulo.
    for (int i = 0; i < 4; ++i) {
        ((char*)(&angulo))[i] = input_serializado[j];
        ++j;
    }
    angulo = ntohl(angulo);
    // Recibo x.
    for (int i = 0; i < 4; ++i) {
        ((char*)(&dest.x))[i] = input_serializado[j];
        ++j;
    }
    dest.x = ntohl(dest.x);
    // Recibo y.
    for (int i = 0; i < 4; ++i) {
        ((char*)(&dest.y))[i] = input_serializado[j];
        ++j;
    }
    dest.y = ntohl(dest.y);
    // Recibo w.
    for (int i = 0; i < 4; ++i) {
        ((char*)(&dest.w))[i] = input_serializado[j];
        ++j;
    }
    dest.w = ntohl(dest.w);
    // Recibo h.
    for (int i = 0; i < 4; ++i) {
        ((char*)(&dest.h))[i] = input_serializado[j];
        ++j;
    }
    dest.h = ntohl(dest.h);

    info_cuerpo.id = id;
    info_cuerpo.angulo = angulo;
    info_cuerpo.dest = dest;
    info_cuerpo.estado = estado;

    if (id == ID_CHELL) {
        if (orientacion == CHELL_MIRA_DERECHA) {
            if (estado == CHELL_CAMBIA_ORIENTACION) {
                info_cuerpo.flip = SDL_FLIP_HORIZONTAL;
            } else {
                info_cuerpo.flip = SDL_FLIP_NONE;
            }
        } else {
            if (estado == CHELL_CAMBIA_ORIENTACION) {
                info_cuerpo.flip = SDL_FLIP_NONE;
            } else {
                info_cuerpo.flip = SDL_FLIP_HORIZONTAL;
            }
        }
    }
}




void Protocolo::terminar(){
    terminado = true;
}
bool Protocolo::termino(){
    return terminado;
}
