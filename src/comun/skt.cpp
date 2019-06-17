
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>
#include <string>

#include <iostream>
#include <sstream>

#include "skt.h"
#include "socket_error.h"

Skt::Skt(std::string host, std::string port) :
    host(std::move(host)),
    port(std::move(port)),
    skt(-1) {
}

Skt::Skt(int skt) : skt(skt) {
}

Skt::Skt(Skt &&otro) {
    this->host = std::move(otro.host);
    this->port = std::move(otro.port);
    this->skt = otro.skt;
    otro.skt = -1;
}

void Skt::conectar() {
    struct addrinfo hints;
    struct addrinfo *result, *ptr;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;

    int s;
    s = getaddrinfo(this->host.c_str(), this->port.c_str(), &hints, &result);

    if (s != 0) {
        std::stringstream ss;
        ss << "Error en getaddrinfo: " << gai_strerror(s) << std::endl;
        throw SocketError(ss.str().c_str());
    }

    int skt = -1;
    bool conectado = false;

    for (ptr = result; ptr != nullptr && !conectado; ptr = ptr->ai_next) {
        skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (skt == -1) {
            continue;
        } else {
            this->skt = skt;
            s = connect(skt, ptr->ai_addr, ptr->ai_addrlen);
            if (s == -1) {
                this->cerrarSocket();
                continue;
            }
            conectado = true;
        }
    }
    freeaddrinfo(result);
    if (skt == -1) {
        throw SocketError("Error al intentar conectarse al server");
    }
}

int Skt::enviarMensaje(char *buffer, int longitud) {
    int byt_enviados = 0;
    int s = 0;

    if ((buffer == nullptr) || (longitud < 1)) {
        throw SocketError("Argumentos invalidos");
    }
    while (byt_enviados < longitud) {
        s = send(skt, buffer+byt_enviados, longitud-byt_enviados,
                MSG_NOSIGNAL);

        if (s == 0) {
            return byt_enviados;
        } else if (s == -1) {
            std::stringstream ss;
            ss << "Error al enviar mensaje: " << strerror(errno) << std::endl;
            throw SocketError(ss.str().c_str());
        }
        byt_enviados += s;
    }
    return byt_enviados;
}

int Skt::leerMensaje(char *buffer, int longitud) {
    int byt_leidos = 0;
    int s = 0;

    if ((buffer == nullptr) || (longitud < 1)) {
        throw SocketError("Argumentos invalidos");
    }
    while (byt_leidos < longitud) {
        s = recv(this->skt, buffer + byt_leidos,
                longitud-byt_leidos, MSG_NOSIGNAL);

        if (s == 0) {
            return byt_leidos;
        } else if (s == -1) {
            std::stringstream ss;
            ss << "Error al leer mensaje: " << strerror(errno) << std::endl;
            throw SocketError(ss.str().c_str());
        }
        byt_leidos += s;
    }
    return byt_leidos;
}

void Skt::cerrarCanalEscritura() {
    shutdown(this->skt, SHUT_WR);
}

void Skt::cerrarCanalLectura() {
    shutdown(this->skt, SHUT_RD);
}

void Skt::cerrarCanales() {
    shutdown(this->skt, SHUT_RDWR);
}

void Skt::cerrarSocket() {
    close(this->skt);
    this->skt = -1;
}

Skt::~Skt() {
    if (this->skt != -1) {
        shutdown(this->skt, SHUT_RDWR);
        this->cerrarSocket();
    }
}
