
#ifndef TH_RENDERIZADO_H
#define TH_RENDERIZADO_H


#include "cola_bloqueante.h"
#include "info_cuerpo.h"
#include "protocolo.h"
#include "renderizador.h"
#include "thread.h"

class ThRenderizado : public Thread {
private:
    ColaBloqueante<MsjRenderizado> &cola_renderizado;
    Protocolo &protocolo;
    Renderizador &renderizador;
    ConvertidorCoordenadas &convertidor_coordenadas;
    bool terminado;
public:
    ThRenderizado(ColaBloqueante<MsjRenderizado> &cola_renderizado,
            Protocolo &protocolo,
            Renderizador &renderizador,
            ConvertidorCoordenadas &convertidor_coordenadas);
    // Recibe la informacion de los cuerpos y la "pushea" en la cola de
    // renderizado para que luego el Renderizador la utilice para renderizar.
    virtual void run();
    // Deja de recibir informacion de cuerpos.
    void terminar();
};


#endif //TH_RENDERIZADO_H
