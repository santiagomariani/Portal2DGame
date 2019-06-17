
#include "ThRenderizado.h"
#include <iostream>

ThRenderizado::ThRenderizado(ColaBloqueante<MsjRenderizado> &cola_renderizado,
        Protocolo &protocolo,
        Renderizador &renderizador,
        ConvertidorCoordenadas &convertidor_coordenadas) :
        cola_renderizado(cola_renderizado),
        protocolo(protocolo),
        renderizador(renderizador),
        convertidor_coordenadas(convertidor_coordenadas),
        terminado(false) {
}

void ThRenderizado::run() {
    while (!terminado) {
        InfoCuerpo info_cuerpo;
        MsjRenderizado msj;
        uint8_t codigo_mensaje = protocolo.recibirCodigoMensaje();
        if (codigo_mensaje == MSJ_FINALIZO_FOTOGRAMA) {
            msj.ultimo = true;
        } else if (codigo_mensaje == MSJ_CUERPO) {
            protocolo.recibirCuerpo(info_cuerpo, convertidor_coordenadas);
            msj.info_cuerpo = std::move(info_cuerpo);
            msj.ultimo = false;
        }
        cola_renderizado.push(msj);
    }
}

void ThRenderizado::terminar() {
    terminado = true;
}
