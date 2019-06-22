
#include "th_esperando_id_partida.h"
#include <iostream>

ThEsperarIdPartida::ThEsperarIdPartida(Protocolo& protocolo, Skt& skt, int* id):
                                        protocolo(protocolo), skt(skt), id(id){
    recibido = false;
}

void ThEsperarIdPartida::terminar(){
    skt.cerrarCanales();
    skt.cerrarSocket();
    recibido = true;
}

bool ThEsperarIdPartida::terminado(){
    return recibido;
}

void ThEsperarIdPartida::run(){
    *id = protocolo.recibirId();
    recibido = true;
}


