#include <fstream>

#include "servidor.h"
#include "SktAceptador.h"
#include "Partida.h"
#include "iniciar_partida.h"

#include "Box2D/Box2D.h"
#include "disparo.h"
#include "BloqueRoca.h"
#include "BloqueMetal.h"
#include "bloque_metal_diagonal.h"
#include "chell.h"
#include "mundo.h"
#include "estado_teclado.h"
#include "personajes.h"
#include "cuerpo.h"
#include "SdlWindow.h"
#include "ViewChell.h"
#include "contact_listener.h"
#include "Timer.h"
#include "Camera.h"
#include "CoordConverter.h"
#include "portal.h"
#include "boton.h"
#include "estado_logico.h"
#include "compuerta.h"
#include "ids.h"
#include "or.h"
#include "and.h"
#include "Roca.h"
#include "BolaEnergia.h"
#include "EmisorArriba.h"
#include "angulo_cero.h"
#include "angulo_noventa.h"
#include "angulo_ciento_ochenta.h"
#include "angulo_dos_setenta.h"
#include "EstadoChell.h"
#include "Protocolo.h"
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

#define TECLA_TERMINAR 'q'

Servidor::Servidor(){
}

void Servidor::iniciar(std::string puerto){
    //
    // Creacion del mundo y el mapa (en realidad no deberia ir aca)
    //
    b2Vec2 gravity(0.0f, -9.8f);
    Mundo mundo(gravity);
    ContactListener listener;
    mundo.setContactListener(listener);

    Personajes personajes(mundo);

    b2Vec2 pos_diago(-12,0);
    AnguloDosSetenta angulo;
    BloqueMetalDiagonal diago(ID_BLOQUE_DIAGONAL_180, mundo, pos_diago, angulo);

    b2Vec2 pos_roca(-8, 0);
    Roca roca(mundo, pos_roca);

    b2Vec2 pos_roca2(-6, 0);
    Roca roca2(mundo, pos_roca2);

    std::vector<BloqueMetal> bloques;
    b2Vec2 pos(-40, -3);
    b2Vec2 inc(1, 0);
    for (int j = 0; j < 45; ++j){
        BloqueMetal bloque(ID_BLOQUE_METAL, mundo, pos);
        bloques.push_back(std::move(bloque));
        pos += inc;
    }

    std::vector<BloqueMetal> pared;
    b2Vec2 pos_bloque(2, -3);
    b2Vec2 inc_pared(0, 1);
    for (int j = 0; j < 2; ++j){
        BloqueMetal roca3(ID_BLOQUE_METAL, mundo, pos_bloque);
        pared.push_back(std::move(roca3));
        pos_bloque += inc_pared;
    }
    pos_bloque.Set(2, 2);
    BloqueMetal bloque_en_el_aire(ID_BLOQUE_METAL, mundo, pos_bloque);

    // Receptores
    b2Vec2 pos_receptor(-17, -2);
    ReceptorArriba receptor_arriba(mundo, pos_receptor);
    /*pos_receptor.Set(-16, 2);
    ReceptorAbajo receptor_abajo(mundo, pos_receptor);
    pos_receptor.Set(-15, 1);
    ReceptorDerecha receptor_derecha(mundo, pos_receptor);
    pos_receptor.Set(-18, 1);
    ReceptorIzquierda receptor_izquierda(mundo, pos_receptor);*/

    b2Vec2 pos_boton(0, -2.35);
    Boton b(pos_boton, mundo);
    //b2Vec2 pos_boton2(-4, -2.35);
    //Boton b2(pos_boton2, mundo);

    EstadoLogico* estado_boton = new EstadoLogico(b); //usar unique pointer?
    //EstadoLogico* estado_boton2 = new EstadoLogico(b2);
    EstadoLogico* estado_receptor = new EstadoLogico(receptor_arriba);

    // con botones OR:
    /*Or compuerta_or;
    compuerta_or.agregar(estado_boton);
    compuerta_or.agregar(estado_receptor);

    b2Vec2 pos_compuerta(-1, -2);
    Compuerta comp(pos_compuerta, mundo, compuerta_or);*/

    // con botones AND:
    And compuerta_and;
    compuerta_and.agregar(estado_boton);
    compuerta_and.agregar(estado_receptor);

    b2Vec2 pos_compuerta(-1, -1.5);
    Compuerta comp(pos_compuerta, mundo, compuerta_and);

    int id = personajes.agregar_chell();

    // Emisores
    b2Vec2 pos_emisor(-16, -2);
    EmisorArriba emisor_arriba(mundo, pos_emisor);
    pos_emisor.Set(-17, 2);
    EmisorAbajo emisor_abajo(mundo, pos_emisor);
    pos_emisor.Set(-22, 1);
    EmisorDerecha emisor_derecha(mundo, pos_emisor);
    pos_emisor.Set(-11, 1);
    EmisorIzquierda emisor_izquierda(mundo, pos_emisor);

    // Acido
    b2Vec2 pos_acido(-24, -2.5 + 0.06);
    Acido acido(mundo, pos_acido);

    // Barra Energia
    b2Vec2 pos_barra_energia(-26, -1.5);
    BarraDeEnergia barra_energia(mundo, pos_barra_energia);

    // b2Vec2 bola_energia_pos(-2, -1);
    // b2Vec2 bola_energia_dir(1, 0);
    // BolaEnergia bola_energia(mundo, bola_energia_pos, bola_energia_dir);

//====_====_====_====_====_====_===_FISICA_====_====_====_====_====_====_===_

    Fisica fisica(mundo);

    //....
    SktAceptador skt(puerto);
    Partida partida(fisica, skt);
    IniciarPartida iniciar_partida(partida);
    iniciar_partida.start();


    char pressed_key = 0;
    while (pressed_key != TECLA_TERMINAR){
        std::cin >> pressed_key;
    }
    iniciar_partida.terminar();
    iniciar_partida.join();
}
