
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

Mensajero &Mensajero::operator<<(float32 numero) {
    uint32_t aux = htonf(numero);
    skt.enviarMensaje((char *) &aux, CUATROBYTES);
    return *this;
}

Mensajero &Mensajero::operator>>(uint8_t &numero) {
    skt.leerMensaje((char *) &numero, UNBYTE);
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
    int32_t aux;
    skt.leerMensaje((char *) &aux, CUATROBYTES);
    numero = ntohl(aux);
    return *this;
}

Mensajero &Mensajero::operator>>(float32 &numero) {
    uint32_t aux;
    skt.leerMensaje((char *) &aux, CUATROBYTES);
    numero = ntohf(aux);
    return *this;
}

float32 Mensajero::ntohf(uint32_t p) {
    float32 f = ((p>>16)&0x7fff);
    f += (p&0xffff) / 65536.0f;

    if (((p>>31)&0x1) == 0x1) { f = -f; }

    return f;
}

uint32_t Mensajero::htonf(float32 f) {
    uint32_t p;
    uint32_t sign;

    if (f < 0) { sign = 1; f = -f; }
    else { sign = 0; }

    p = ((((uint32_t)f)&0x7fff)<<16) | (sign<<31);
    p |= (uint32_t)(((f - (int)f) * 65536.0f))&0xffff;

    return p;
}
