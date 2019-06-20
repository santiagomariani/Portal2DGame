
#ifndef THVIDEO_H
#define THVIDEO_H


#include <thread.h>
#include <vector>
#include <cola_bloqueante.h>
#include "contexto_formato.h"
#include "formato_salida.h"

class ThVideo : public Thread {
private:
    const int ancho_buffer, alto_buffer;
    ContextoFormato contexto_formato;
    FormatoSalida formato_salida;
    SwsContext *ctx;
    ColaBloqueante<std::vector<char>> cola_buffer;
public:
    ThVideo(int ancho_buffer, int alto_buffer);
    void run();
    void terminar();
    ~ThVideo();
};


#endif //THVIDEO_H
