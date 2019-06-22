
#ifndef THVIDEO_H
#define THVIDEO_H


#include <thread.h>
#include <vector>
#include <cola_bloqueante.h>
#include "contexto_formato.h"
#include "formato_salida.h"

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

class ThVideo : public Thread {
private:
    ColaBloqueante<std::vector<char>> &cola_buffer;
    std::unique_ptr<ContextoFormato> contexto_formato;
    std::unique_ptr<FormatoSalida> formato_salida;
    SwsContext *ctx;
public:
    ThVideo(ColaBloqueante<std::vector<char>> &cola_buffer,
            int ancho,
            int alto);
    void run();
    void terminar();
    ~ThVideo();
};


#endif //THVIDEO_H
