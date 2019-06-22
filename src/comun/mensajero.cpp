
#include <arpa/inet.h>
#include <string>
#include <SDL2/SDL_quit.h>
#include <Box2D/Common/b2Settings.h>

#include "mensajero.h"

#define UNBYTE 1
#define DOSBYTES 2
#define CUATROBYTES 4

Mensajero::Mensajero(Skt &skt) : skt(skt) {
}

Mensajero &Mensajero::operator<<(uint8_t numero) {
    skt.enviarMensaje((char *) &numero, UNBYTE);
    return *this;
}

Mensajero &Mensajero::operator<<(uint16_t numero) {
    numero = htons(numero);
    skt.enviarMensaje((char *) &numero, DOSBYTES);
    return *this;
}

Mensajero &Mensajero::operator<<(uint32_t numero) {
    numero = htonl(numero);
    skt.enviarMensaje((char *) &numero, CUATROBYTES);
    return *this;
}

Mensajero &Mensajero::operator<<(std::string &cadena) {
    uint32_t longitud = cadena.size();
    *this << longitud;
    skt.enviarMensaje(&cadena[0], longitud);
    return *this;
}

Mensajero &Mensajero::operator<<(int32_t numero) {
    numero = htonl(numero);
    skt.enviarMensaje((char *) &numero, CUATROBYTES);
    return *this;
}

Mensajero &Mensajero::operator>>(uint8_t &numero) {
    uint8_t aux;
    skt.leerMensaje((char *) &aux, UNBYTE);
    numero = aux;
    return *this;
}

Mensajero &Mensajero::operator>>(uint16_t &numero) {
    uint16_t aux;
    skt.leerMensaje((char *) &aux, DOSBYTES);
    numero = ntohs(aux);
    return *this;
}

Mensajero &Mensajero::operator>>(uint32_t &numero) {
    uint32_t aux;
    skt.leerMensaje((char *) &aux, CUATROBYTES);
    numero = ntohl(aux);
    return *this;
}

Mensajero &Mensajero::operator>>(std::string &cadena) {
    uint32_t longitud;
    *this >> longitud;
    cadena.resize(longitud);
    skt.leerMensaje((char *) &cadena[0], longitud);
    return *this;
}

Mensajero &Mensajero::operator>>(int32_t &numero) {
    uint32_t aux;
    skt.leerMensaje((char *) &aux, CUATROBYTES);
    numero = ntohl(aux);
    return *this;
}


