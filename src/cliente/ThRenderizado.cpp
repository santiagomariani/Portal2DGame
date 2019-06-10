//
// Created by santi on 09/06/19.
//

#include "ThRenderizado.h"
#include <iostream>

ThRenderizado::ThRenderizado(ColaBloqueante<InfoCuerpo> &cola_renderizado,
        Protocolo &protocolo,
        Renderizador &renderizador,
        CoordConverter &coord_converter) :
        cola_renderizado(cola_renderizado),
        protocolo(protocolo),
        renderizador(renderizador),
        coord_converter(coord_converter),
        terminado(false) {
}

void ThRenderizado::run() {
    while (!terminado) {
        InfoCuerpo info_cuerpo;
        uint8_t codigo_mensaje = protocolo.recibirCodigoMensaje();
        if (codigo_mensaje == MSJ_FINALIZO_FOTOGRAMA) {
            renderizador.finalizoFotograma();
        } else if (codigo_mensaje == MSJ_CUERPO) {
            protocolo.recibirCuerpo(info_cuerpo, coord_converter);
            cola_renderizado.push(info_cuerpo);
            std::cout << "cuerpo recibido\n";
        }
    }
}

void ThRenderizado::terminar() {
    terminado = true;
}
