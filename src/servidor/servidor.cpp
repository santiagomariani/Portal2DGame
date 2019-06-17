#include <iostream>

#include "servidor.h"
#include "skt_aceptador.h"
#include "partida.h"
#include "iniciar_partida.h"

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
#include "BolaEnergia.h"
#include "EmisorArriba.h"
#include "angulo_cero.h"
#include "angulo_noventa.h"
#include "angulo_ciento_ochenta.h"
#include "angulo_dos_setenta.h"
#include "estado_chell.h"
#include "protocolo.h"
#include "fisica.h"
#include "EmisorAbajo.h"
#include "EmisorDerecha.h"
#include "EmisorIzquierda.h"
#include "ReceptorArriba.h"
#include "ReceptorAbajo.h"
#include "ReceptorDerecha.h"
#include "ReceptorIzquierda.h"
#include "Acido.h"
#include "BarraDeEnergia.h"
#include "config.h"
#include "th_aceptador_clientes.h"

#define TECLA_TERMINAR 'q'
#define TECLA_TERMINAR_RECIBIR_CLIENTES 't'

Servidor::Servidor(){
}

void Servidor::iniciarMultiPartidas(std::string puerto){
    SktAceptador skt_aceptador(puerto);
    ThAceptadorClientes aceptador_clientes(std::move(skt_aceptador));
    aceptador_clientes.start();
    
    char tecla = 0;
    while (tecla != TECLA_TERMINAR){
        std::cin >> tecla;
    }
    aceptador_clientes.terminar();
    aceptador_clientes.join();
}

void Servidor::iniciar(std::string puerto){

}

Servidor::~Servidor(){}
