
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include "ThVideo.h"

ThVideo::ThVideo(int ancho_buffer, int alto_buffer) :
    ancho_buffer(ancho_buffer),
    alto_buffer(alto_buffer) {
    av_register_all();
    // Calculo fecha
    std::string nombre_prueba("nombre_prueba");
    //
    formato_salida = FormatoSalida(contexto_formato, nombre_prueba);
    SwsContext * ctx = sws_getContext(ancho_buffer,
            alto_buffer,
            AV_PIX_FMT_RGB24,
            ancho_buffer,
            alto_buffer,
            AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
}

void ThVideo::run() {
    std::vector<char> buffer;
    while (cola_buffer.pop(buffer)) {
        formato_salida.writeFrame(buffer.data(), ctx);
    }
    formato_salida.close();
}

void ThVideo::terminar() {
    cola_buffer.finalizado();
}

ThVideo::~ThVideo() {
    sws_freeContext(ctx);
}
