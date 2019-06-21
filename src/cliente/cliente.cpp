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
                         NULL);
        *etapa = 0;
        return;
    }
    
    Skt skt_partida(host, puerto_partida);
    
    skt_partida.conectar();

    std::cout << "partida creada\n";

    Mensajero mensajero(skt_partida); // poner en pantalla el puerto de la partida
    Protocolo protocolo(mensajero);
    int id;
    try {
        id = protocolo.recibirId();
        std::cout << "id recibido es: " << +id << std::endl;
    } catch (SocketError& e) {
        PantallaErrorPartida error_partida;
        error_partida();
        *etapa = 0;
        return;
    }

    const int ancho_nivel = 1280;
    const int alto_nivel = 720;

    Ventana ventana(ancho_nivel, alto_nivel);
    Mixer();

    // Disparo.
    std::string arch_textura_efectos = "assets/fx.png";
    Textura textura_efectos(arch_textura_efectos, ventana);
    Sprite sprite_disparo(111, 59, 1, 1920, 3, textura_efectos);

    // Bloques roca y metal.
    std::string arch_textura_bloques = "assets/blocks1.png";
    Textura textura_bloques(arch_textura_bloques, ventana);
    Sprite sprite_bloque(193, 193, 1, 172, 1, textura_bloques);
    Sprite sprite_bloque_metal(193, 193, 1, 600, 1, textura_bloques);
    std::string arch_textura_bloque_diag_0 = "assets/block-diago.png";
    Textura textura_bloque_diag_0(arch_textura_bloque_diag_0, ventana);
    Sprite sprite_bloque_diag_0(178, 177, 0, 2, 1, textura_bloque_diag_0);
    std::string arch_textura_bloque_diag_90 = "assets/diago-90.png";
    Textura textura_bloque_diag_90(arch_textura_bloque_diag_90, ventana);
    Sprite sprite_bloque_diag_90(177, 178, 2, 0, 1, textura_bloque_diag_90);
    std::string arch_textura_bloque_diag_180 = "assets/diago-180.png";
    Textura textura_bloque_diag_180(arch_textura_bloque_diag_180, ventana);
    Sprite sprite_bloque_diag_180(177, 178, 2, 0, 1, textura_bloque_diag_180);
    std::string arch_textura_bloque_diag_270 = "assets/diago-270.png";
    Textura textura_bloque_diag_270(arch_textura_bloque_diag_270, ventana);
    Sprite sprite_bloque_diag_270(177, 178, 2, 0, 1, textura_bloque_diag_270);

    // Boton apagado y prendidos.
    std::string arch_textura_varios = "assets/miscellaneous.png";
    Textura textura_varios(arch_textura_varios, ventana);
    Sprite sprite_boton(175, 55, 1, 116, 1, textura_varios);
    Sprite sprite_boton_prendido(175, 74, 1, 192, 1, textura_varios);

    // Compuerta cerrada y abierta.
    std::string arch_textura_compuerta = "assets/gate.png";
    Textura textura_compuerta(arch_textura_compuerta, ventana);
    Sprite sprite_compuerta_cerrada(193, 385, 1, 21, 1, textura_compuerta);
    Sprite sprite_compuerta_abierta(193, 385, 1553, 2437, 1, textura_compuerta);
    Sprite sprite_compuerta_abriendo(193, 385, 1, 2051, 19, textura_compuerta);

    // Portal azul.
    std::string arch_textura_portal_azul = "assets/portAzul.png";
    Textura textura_portal_azul(arch_textura_portal_azul, ventana);
    Sprite sprite_portal_azul(193, 193, 0, 0, 1, textura_portal_azul);

    // Portal naranja.
    std::string arch_textura_portal_naranja = "assets/portNaranja.png";
    Textura textura_portal_naranja(arch_textura_portal_naranja, ventana);
    Sprite sprite_portal_naranja(193, 193, 0, 0, 1, textura_portal_naranja);

    // Piedras.
    Sprite sprite_piedra1(85, 83, 1, 4513, 1, textura_efectos);
    Sprite sprite_piedra2(85, 83, 87, 4513, 1, textura_efectos);
    Sprite sprite_piedra3(85, 83, 173, 4513, 1, textura_efectos);
    Sprite sprite_piedra4(85, 83, 259, 4513, 1, textura_efectos);
    Sprite sprite_piedra5(85, 83, 345, 4513, 1, textura_efectos);
    Sprite sprite_piedra6(85, 83, 431, 4513, 1, textura_efectos);
    Sprite sprite_piedra7(85, 83, 517, 4513, 1, textura_efectos);
    Sprite sprite_piedra8(85, 83, 603, 4513, 1, textura_efectos);

    // Bola de energia.
    Sprite sprite_bola_de_energia(171, 119, 1, 2000, 5, textura_efectos);

    // EmisorArriba.
    Sprite sprite_emisor_arriba(193, 193, 1, 1242, 1, textura_bloques);
    // EmisorDerecha.
    Sprite sprite_emisor_derecha(193, 193, 1, 1028, 1, textura_bloques);
    // EmisorAbajo.
    Sprite sprite_emisor_abajo(193, 193, 1, 1456, 1, textura_bloques);
    // EmisorIzquierda.
    Sprite sprite_emisor_izquierda(193, 193, 1, 814, 1, textura_bloques);

    // Receptores.

    // ReceptorArriba.
    // 	Activado.
    Sprite sprite_receptor_arriba_activado(192, 192, 466, 1243, 1, 
            textura_bloques);
    // Desactivado.
    Sprite sprite_receptor_arriba_desactivado(192, 192, 233, 1243, 1, 
            textura_bloques);

    // ReceptorDerecha.
    // 	Activado.
    Sprite sprite_receptor_derecha_activado(192, 192, 465, 1029, 1,
            textura_bloques);
    // Desactivado.
    Sprite sprite_receptor_derecha_desactivado(192, 192, 235, 1029, 1,
            textura_bloques);

    // ReceptorIzquierda.
    // 	Activado.
    Sprite sprite_receptor_izquierda_activado(192, 192, 464, 814, 1, 
            textura_bloques);
    // Desactivado.
    Sprite sprite_receptor_izquierda_desactivado(192, 192, 235, 814, 1,
            textura_bloques);

    // ReceptorAbajo.
    // 	Activado.
    Sprite sprite_receptor_abajo_activado(192, 192, 468, 1457, 1,
            textura_bloques);
    // Desactivado.
    Sprite sprite_receptor_abajo_desactivado(192, 192, 232, 1457, 1, 
            textura_bloques);

    // Acido.
    Sprite sprite_acido(300, 61, 1, 1545, 8, textura_varios);

    // Barra Energia.
    Sprite sprite_barra_energia(8, 220, 528, 689, 1, textura_varios);

    // Torta
    std::string arch_textura_torta = "assets/torta.png";
    Textura textura_torta(arch_textura_torta, ventana);
    Sprite sprite_torta(381, 389, 0, 0, 1, textura_torta);

    ColeccionVistaChells coleccion_viewchells(ventana);

    std::map<uint8_t,Renderizable*> renderizables;
    renderizables[ID_BLOQUE_ROCA] = &sprite_bloque;
    renderizables[ID_DISPARO] = &sprite_disparo;
    renderizables[ID_BLOQUE_METAL] = &sprite_bloque_metal;
    renderizables[ID_BLOQUE_DIAGONAL_0] = &sprite_bloque_diag_0;
    renderizables[ID_BLOQUE_DIAGONAL_90] = &sprite_bloque_diag_90;
    renderizables[ID_BLOQUE_DIAGONAL_180] = &sprite_bloque_diag_180;
    renderizables[ID_BLOQUE_DIAGONAL_270] = &sprite_bloque_diag_270;
    renderizables[ID_PORTAL_AZUL] = &sprite_portal_azul;
    renderizables[ID_PORTAL_NARANJA] = &sprite_portal_naranja;
    renderizables[ID_BOTON_APAGADO] = &sprite_boton;
    renderizables[ID_COMPUERTA_CERRADA] = &sprite_compuerta_cerrada;
    renderizables[ID_COMPUERTA_ABRIENDO] = &sprite_compuerta_abriendo;
    renderizables[ID_COMPUERTA_ABIERTA] = &sprite_compuerta_abierta;
    renderizables[ID_ROCA] = &sprite_piedra1;
    renderizables[ID_BOTON_PRENDIDO] = &sprite_boton_prendido;
    renderizables[ID_EMISORARRIBA] = &sprite_emisor_arriba;
    renderizables[ID_EMISORDERECHA] = &sprite_emisor_derecha;
    renderizables[ID_EMISORABAJO] = &sprite_emisor_abajo;
    renderizables[ID_EMISORIZQUIERDA] = &sprite_emisor_izquierda;
    renderizables[ID_BOLAENERGIA] = &sprite_bola_de_energia;
    renderizables[ID_RECEPTORARRIBA_ACTIVADO] =
            &sprite_receptor_arriba_activado;
    renderizables[ID_RECEPTORARRIBA_DESACTIVADO] = 
            &sprite_receptor_arriba_desactivado;
    renderizables[ID_RECEPTORDERECHA_ACTIVADO] =
            &sprite_receptor_derecha_activado;
    renderizables[ID_RECEPTORDERECHA_DESACTIVADO] =
            &sprite_receptor_derecha_desactivado;
    renderizables[ID_RECEPTORABAJO_ACTIVADO] =
            &sprite_receptor_abajo_activado;
    renderizables[ID_RECEPTORABAJO_DESACTIVADO] = 
            &sprite_receptor_abajo_desactivado;
    renderizables[ID_RECEPTORIZQUIERDA_ACTIVADO] =
            &sprite_receptor_izquierda_activado;
    renderizables[ID_RECEPTORIZQUIERDA_DESACTIVADO] = 
            &sprite_receptor_izquierda_desactivado;
    renderizables[ID_ACIDO] = &sprite_acido;
    renderizables[ID_BARRAENERGIA] = &sprite_barra_energia;
    renderizables[ID_TORTA] = &sprite_torta;

    std::string arch_musica_en_juego("assets/sonidos/musica_juego.wav");
    Musica musica_en_juego(arch_musica_en_juego);
    musica_en_juego.setearVolumen(MIX_MAX_VOLUME / 5);
    Mix_AllocateChannels(16);

	std::string arch_fondo = "assets/industrial-background.jpg";
	Textura fondo(arch_fondo, ventana);
	Camara camara(ancho_nivel, alto_nivel, fondo);

	ConvertidorCoordenadas convertidor_coordenadas(ancho_nivel, ancho_nivel);
	ColaBloqueante<Input> cola_input;
	ObtenedorInput obtenedor_input(convertidor_coordenadas,
	        camara,
	        cola_input,
	        ventana);

	
	ThInput th_input(cola_input, protocolo, id);

	ColaBloqueante<MsjRenderizado> cola_renderizado;

	Renderizador renderizador(ventana,
			camara,
			cola_renderizado,
			renderizables,
			id,
			coleccion_viewchells);

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

std::string Cliente::requestNuevaPartida(Protocolo& protocolo){
    std::cout << "enviando nueva partida request\n";
    protocolo.enviarOpcionNuevaPartida();
    std::cout << "enviado req\n";
    std::string puerto_partida("8081");
    protocolo.enviarPuerto(puerto_partida);
    uint8_t respuesta = protocolo.recibirCodigoMensaje();
    if (respuesta != MSJ_PARTIDA_CREADA){
        return std::string(); // error al crear el socket en el servidor
    }
    return puerto_partida;
}

std::string Cliente::requestUnirsePartida(Protocolo& protocolo){
    protocolo.enviarOpcionUnirsePartida();
    std::string puerto_partida("8081");
    return puerto_partida;
}
