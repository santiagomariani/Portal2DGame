

#ifndef MENSAJERO_H
#define MENSAJERO_H


#include <cstdint>
#include <string>

#include "Skt.h"

// Sabe como enviar y recibir distintos tipos de datos.
class Mensajero {
private:
    Skt &skt;
    uint32_t htonf(float f);
    float ntohf(uint32_t p);
public:
    explicit Mensajero(Skt &skt);
    // Envia un uint8_t.
    Mensajero& operator<<(uint8_t numero);
    // Envia un uint16_t.
    Mensajero& operator<<(uint16_t numero);
    // Envia un uint32_t.
    Mensajero& operator<<(uint32_t numero);
    // Envia una cadena. Enviando primero la longitud
    // en un uint32_t.
    Mensajero& operator<<(std::string &cadena);
    // Envia Sint32.
    Mensajero& operator<<(int32_t numero);
    // Envia float.
    Mensajero& operator<<(float numero);
    // Recibe un uint8_t.
    Mensajero& operator>>(uint8_t& numero);
    // Recibe un uint16_t.
    Mensajero& operator>>(uint16_t& numero);
    // Recibe un uint32_t.
    Mensajero& operator>>(uint32_t& numero);
    // Recibe una cadena.
    Mensajero& operator>>(std::string &cadena);
    // Recibe Sint32.
    Mensajero& operator>>(int32_t& numero);
    // Recibe float.
    Mensajero& operator>>(float &numero);
    ~Mensajero() = default;
};


#endif //MENSAJERO_H
