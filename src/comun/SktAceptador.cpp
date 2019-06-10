//
// Created by santi on 21/04/19.
//


#define _POSIX_C_SOURCE 200112L

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

#include "SktAceptador.h"
#include "SocketError.h"
#include "Skt.h"

#define MAX_CLIENTES 10

SktAceptador::SktAceptador(std::string port) :
    port(std::move(port)),
    skt(-1) {
}

SktAceptador::SktAceptador(SktAceptador &&other) {
    this->skt = other.skt;
    this->port = std::move(other.port);
    other.skt = -1;
}

void SktAceptador::escucharClientes() {
    struct addrinfo hints;
    struct addrinfo *ptr;

    int s = 0;

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(nullptr, this->port.c_str(), &hints, &ptr);

    if (s != 0) {
        std::stringstream ss;
        ss << "Error en getaddrinfo: "<< gai_strerror(s) << std::endl;
        throw SocketError(ss.str().c_str());
    }
    int skt; // Socket aceptador.
    skt = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (skt == -1) {
        freeaddrinfo(ptr);
        std::stringstream ss;
        ss << "Error: "<< strerror(errno) << std::endl;
        throw SocketError(ss.str().c_str());
    }
    int val = 1;
    s = setsockopt(skt, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    if (s == -1) {
        freeaddrinfo(ptr);
        close(skt);
        std::stringstream ss;
        ss << "Error: "<< strerror(errno) << std::endl;
        throw SocketError(ss.str().c_str());
    }
    s = bind(skt, ptr->ai_addr, ptr->ai_addrlen);

    if (s == -1) {
        freeaddrinfo(ptr);
        close(skt);
        std::stringstream ss;
        ss << "Error: "<< strerror(errno) << std::endl;
        throw SocketError(ss.str().c_str());
    }
    freeaddrinfo(ptr);
    s = listen(skt, MAX_CLIENTES);

    if (s == -1) {
        close(skt);
        std::stringstream ss;
        ss << "Error: "<< strerror(errno) << std::endl;
        throw SocketError(ss.str().c_str());
    }
    this->skt = skt;
}

Skt SktAceptador::aceptarCliente() {
    int skt_cliente = accept(this->skt, nullptr, nullptr);
    if (skt_cliente == -1){
        throw SocketError("Error al aceptar cliente.");
    }
    return std::move(Skt(skt_cliente));
}

void SktAceptador::cerrarCanales() {
    shutdown(this->skt, SHUT_RDWR);
}

void SktAceptador::cerrarSocket() {
    close(this->skt);
    this->skt = -1;
}

SktAceptador::~SktAceptador() {
    if (this->skt != -1) {
        shutdown(this->skt, SHUT_RDWR);
        close(this->skt);
    }
}
