
#include <iostream>
#include <sstream>
#include <iomanip>
#include <path.h>
#include "th_video.h"

ThVideo::ThVideo(ColaBloqueante<std::vector<char>> &cola_buffer,
                 int ancho,
                 int alto) :
    cola_buffer(cola_buffer) {

    av_register_all();

    std::time_t t = std::time(nullptr);
    std::tm *fecha = std::localtime(&t);
    std::stringstream oss;
    oss << std::put_time(fecha, "%b %d %H:%M:%S %Y");
    std::string nombre_archivo = std::string(ASSETS) + oss.str();


    contexto_formato.reset(new ContextoFormato());
    formato_salida.reset(new FormatoSalida(nombre_archivo, ancho, alto));
    
    ctx = sws_getContext(ancho,
            alto,
            AV_PIX_FMT_RGB24,
            ancho,
            alto,
            AV_PIX_FMT_YUV420P, 0, 0, 0, 0);
}

void ThVideo::run() {
    std::vector<char> buffer;
    while (cola_buffer.pop(buffer)) {
        formato_salida->escribirMarco(buffer.data(), ctx);
    }
    formato_salida->cerrar();
}

void ThVideo::terminar() {
    cola_buffer.finalizado();
}

ThVideo::~ThVideo() {
    sws_freeContext(ctx);
}
