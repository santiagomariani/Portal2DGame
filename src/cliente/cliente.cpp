#include "cliente.h"
#include "estado_mouse.h"
#include "convertidor_coordenadas.h"
#include "vista_chell.h"
#include "info_cuerpo.h"
#include "ids.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <socket_error.h>
#include "Box2D/Box2D.h"
#include "obtenedor_input.h"
#include "renderizador.h"
#include "cola_bloqueante.h"
#include "input.h"
#include "th_input.h"
#include "skt.h"
#include "th_renderizado.h"
#include "msj_renderizado.h"
#include "sonido.h"
#include "mixer.h"
#include "musica.h"
#include "coleccion_vista_chells.h"
#include "pantalla_error_partida.h"
#include "pantalla_elegir_partida.h"
#include "pantalla_esperando.h"


void Cliente::iniciar(int* etapa) {
    // Conexion con servidor.
    std::string host = "localhost";
    std::string port = "8080";

    // ELEGIR NUEVA PARTIDA O UNIRSE A PARTIDA
    // ...
    std::string puerto_partida;
    try {
        PantallaElegirPartida elegir_partida(port, host, puerto_partida);
        if (!elegir_partida()){
            *etapa = 0; // volver a inicio
            return; // cerrar programa (o ventana)
        }
    } catch (SocketError& e){
        //PantallaErrorPartida error_partida;
        //error_partida();
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                         "Error",
                         "Hubo un error en la conexion",
                         nullptr);
        *etapa = 0;
        return;
    }
    
    Skt skt_partida(host, puerto_partida);
    
    skt_partida.conectar();

    // poner en pantalla el puerto de la partida
    Mensajero mensajero(skt_partida);
    Protocolo protocolo(mensajero);
    uint8_t id;
    int id_recib = -1;
    try {
        PantallaEsperando esperando;
        id_recib = esperando(protocolo, skt_partida);
        if (id_recib < 0){
            *etapa = 0;
            return;
        }
    } catch (SocketError& e) {
        *etapa = 0;
        return;
    }
    id = (uint8_t)id_recib;

    const int ancho_nivel = 1280;
    const int alto_nivel = 720;

    Ventana ventana(ancho_nivel, alto_nivel);
    Mixer mixer;

    ColeccionVistaChells coleccion_viewchells(ventana);
    ColeccionSprites coleccion_sprites(ventana);

    std::string arch_musica_en_juego("assets/sonidos/musica_juego.wav");
    Musica musica_en_juego(arch_musica_en_juego);
    musica_en_juego.setearVolumen(MIX_MAX_VOLUME / 5);
    Mix_AllocateChannels(16);
 
    int ancho_buffer = ancho_nivel;
    int alto_buffer = alto_nivel;
    Grabador grabador(ventana, ancho_buffer, alto_buffer);

    std::string arch_fondo = "assets/industrial-background.jpg";
    Textura fondo(arch_fondo, ventana);
    Camara camara(ancho_nivel, alto_nivel, fondo, grabador);

    ConvertidorCoordenadas convertidor_coordenadas(ancho_nivel, ancho_nivel);
    ColaBloqueante<Input> cola_input;


    ObtenedorInput obtenedor_input(
            camara,
            cola_input,
            ventana, convertidor_coordenadas, grabador);

    ThInput th_input(cola_input, protocolo, id);

    ColaBloqueante<MsjRenderizado> cola_renderizado;


    Renderizador renderizador(
            camara,
            cola_renderizado,
            coleccion_sprites,
            id,
            coleccion_viewchells, ventana, grabador);

    ThRenderizado th_renderizado(cola_renderizado,
            protocolo,
            renderizador,
            convertidor_coordenadas);

    th_input.start();
    th_renderizado.start();
    bool seguir = true;
    musica_en_juego.reproducirEnLoop();
    ContadorTiempo contador_tiempo;
    while(seguir) {
        contador_tiempo.comenzar();
        seguir = obtenedor_input.obtenerInput();
        renderizador.renderizar();
        int ticks_fotograma = contador_tiempo.obtenerTicks();
        if (ticks_fotograma < TICKS_POR_FOTOGRAMA) {
            SDL_Delay(TICKS_POR_FOTOGRAMA - ticks_fotograma);
        }
    }
    th_renderizado.terminar();
    th_renderizado.join();
    th_input.terminar();
    th_input.join();
}
