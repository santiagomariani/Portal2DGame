
#include <iostream>
#include "servidor.h"
#include "skt_aceptador.h"
#include "partida.h"
#include "Box2D/Box2D.h"
#include "disparo.h"
#include "bloque_roca.h"
#include "bloque_metal.h"
#include "bloque_metal_diagonal.h"
#include "chell.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "personajes.h"
#include "cuerpo.h"
#include "contact_listener.h"
#include "convertidor_coordenadas.h"
#include "portal.h"
#include "boton.h"
#include "estado_logico.h"
#include "compuerta.h"
#include "ids.h"
#include "or.h"
#include "and.h"
#include "roca.h"
#include "bola_energia.h"
#include "emisor_arriba.h"
#include "angulo_cero.h"
#include "angulo_noventa.h"
#include "angulo_ciento_ochenta.h"
#include "angulo_dos_setenta.h"
#include "estado_chell.h"
#include "protocolo.h"
#include "fisica.h"
#include "emisor_abajo.h"
#include "emisor_derecha.h"
#include "emisor_izquierda.h"
#include "receptor_arriba.h"
#include "receptor_abajo.h"
#include "receptor_derecha.h"
#include "receptor_izquierda.h"
#include "acido.h"
#include "barra_de_energia.h"
#include "config.h"
#include "th_aceptador_clientes.h"

#define TECLA_TERMINAR 'q'

Servidor::Servidor(){
}

void Servidor::iniciarMultiPartidas(std::string puerto){
    SktAceptador skt_aceptador(puerto);
    ThAceptadorClientes aceptador_clientes(std::move(skt_aceptador), puerto);
    aceptador_clientes.start();
    
    char tecla = 0;
    while (tecla != TECLA_TERMINAR){
        std::cin >> tecla;
    }
    aceptador_clientes.terminar();
    aceptador_clientes.join();
}


Servidor::~Servidor(){}
