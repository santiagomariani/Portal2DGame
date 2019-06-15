#include "Cliente.h"
#include "estado_mouse.h"
#include "CoordConverter.h"
#include "ViewChell.h"
#include "InfoCuerpo.h"
#include "ids.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Box2D/Box2D.h"
#include "ObtenedorInput.h"
#include "Renderizador.h"
#include "ColaBloqueante.h"
#include "Input.h"
#include "ThInput.h"
#include "Skt.h"
#include "ThRenderizado.h"
#include "msj_renderizado.h"
#include "Sonido.h"
#include "Mixer.h"
#include "Musica.h"
#include "ColeccionViewChells.h"

void Cliente::iniciar() {

    const int ancho_nivel = 1280;
    const int alto_nivel = 720;

    Ventana ventana(ancho_nivel, alto_nivel);
    Mixer();

    // Disparo
    std::string arch_textura_efectos = "assets/fx.png";
    Textura textura_efectos(arch_textura_efectos, ventana);
    Sprite disparoSprite(111, 59, 1, 1920, 3, textura_efectos);

    // Bloques roca y metal
    std::string blocksPath = "assets/blocks1.png";
    Textura blocksTexture(blocksPath, ventana);
    Sprite bloqueSprite(193, 193, 1, 172, 1, blocksTexture);
    Sprite bloqueMetalSprite(193, 193, 1, 600, 1, blocksTexture);
    std::string diago_path = "assets/block-diago.png";
    Textura diago_texture(diago_path, ventana);
    Sprite bloqueMetalDiagoSprite(178, 177, 0, 2, 1, diago_texture);
    std::string diago90_path = "assets/diago-90.png";
    Textura diago90_texture(diago90_path, ventana);
    Sprite bloqueMetalDiago90Sprite(177, 178, 2, 0, 1, diago90_texture);
    std::string diago180_path = "assets/diago-180.png";
    Textura diago180_texture(diago180_path, ventana);
    Sprite bloqueMetalDiago180Sprite(177, 178, 2, 0, 1, diago180_texture);
    std::string diago270_path = "assets/diago-270.png";
    Textura diago270_texture(diago270_path, ventana);
    Sprite bloqueMetalDiago270Sprite(177, 178, 2, 0, 1, diago270_texture);

    // Boton apagado y prendidos
    std::string botonPath = "assets/miscellaneous.png";
    Textura miscTexture(botonPath, ventana);
    Sprite botonSprite(175, 55, 1, 116, 1, miscTexture);
    Sprite botonPrendidoSprite(175, 74, 1, 192, 1, miscTexture);

    // Compuerta cerrada y abierta
    std::string compuertaPath = "assets/gate.png";
    Textura compuertaTexture(compuertaPath, ventana);
    Sprite compuertaCerradaSprite(193, 385, 1, 21, 1, compuertaTexture);
    Sprite compuertaAbiertaSprite(193, 385, 1553, 2437, 1, compuertaTexture);
    Sprite compuertaAbriendoSprite(193, 385, 1, 2051, 19, compuertaTexture);

    //Portal azul
    std::string portalAzulPath = "assets/portAzul.png";
    Textura portalAzulTexture(portalAzulPath, ventana);
    Sprite portalAzulSprite(193, 193, 0, 0, 1, portalAzulTexture);

    //Portal naranja
    std::string portalNaranjaPath = "assets/portNaranja.png";
    Textura portalNaranjaTexture(portalNaranjaPath, ventana);
    Sprite portalNaranjaSprite(193, 193, 0, 0, 1, portalNaranjaTexture);

    // Piedra
    Sprite piedra_sprite1(85, 83, 1, 4513, 1, textura_efectos);
    Sprite piedra_sprite2(85, 83, 87, 4513, 1, textura_efectos);
    Sprite piedra_sprite3(85, 83, 173, 4513, 1, textura_efectos);
    Sprite piedra_sprite4(85, 83, 259, 4513, 1, textura_efectos);
    Sprite piedra_sprite5(85, 83, 345, 4513, 1, textura_efectos);
    Sprite piedra_sprite6(85, 83, 431, 4513, 1, textura_efectos);
    Sprite piedra_sprite7(85, 83, 517, 4513, 1, textura_efectos);
    Sprite piedra_sprite8(85, 83, 603, 4513, 1, textura_efectos);

    // Bola de energia.
    Sprite bola_energia_sprite(171, 119, 1, 2000, 5, textura_efectos);

    // EmisorArriba
    Sprite emisor_arriba_sprite(193, 193, 1, 1242, 1, blocksTexture);
    // EmisorDerecha
    Sprite emisor_derecha_sprite(193, 193, 1, 1028, 1, blocksTexture);
    // EmisorAbajo
    Sprite emisor_abajo_sprite(193, 193, 1, 1456, 1, blocksTexture);
    // EmisorIzquierda
    Sprite emisor_izquierda_sprite(193, 193, 1, 814, 1, blocksTexture);

    // Receptores

    // ReceptorArriba
    // 	Activado
    Sprite receptor_arriba_activado_sprite(192, 192, 466, 1243, 1, blocksTexture);
    // Desactivado
    Sprite receptor_arriba_desactivado_sprite(192, 192, 233, 1243, 1, blocksTexture);

    // ReceptorDerecha
    // 	Activado
    Sprite receptor_derecha_activado_sprite(192, 192, 465, 1029, 1, blocksTexture);
    // Desactivado
    Sprite receptor_derecha_desactivado_sprite(192, 192, 235, 1029, 1, blocksTexture);

    // ReceptorIzquierda
    // 	Activado
    Sprite receptor_izquierda_activado_sprite(192, 192, 464, 814, 1, blocksTexture);
    // Desactivado
    Sprite receptor_izquierda_desactivado_sprite(192, 192, 235, 814, 1, blocksTexture);

    // ReceptorAbajo
    // 	Activado
    Sprite receptor_abajo_activado_sprite(192, 192, 468, 1457, 1, blocksTexture);
    // Desactivado
    Sprite receptor_abajo_desactivado_sprite(192, 192, 232, 1457, 1, blocksTexture);

    // Acido
    Sprite acido_sprite(300, 61, 1, 1545, 8, miscTexture);

    // Barra Energia
    Sprite barra_energia_sprite(8, 220, 528, 689, 1, miscTexture);

    ColeccionViewChells coleccion_viewchells(ventana);

    std::map<uint8_t,Renderable*> renderizables;
    renderizables[ID_BLOQUE_ROCA] = &bloqueSprite;
    renderizables[ID_DISPARO] = &disparoSprite;
    renderizables[ID_BLOQUE_METAL] = &bloqueMetalSprite;
    renderizables[ID_BLOQUE_DIAGONAL_0] = &bloqueMetalDiagoSprite;
    renderizables[ID_BLOQUE_DIAGONAL_90] = &bloqueMetalDiago90Sprite;
    renderizables[ID_BLOQUE_DIAGONAL_180] = &bloqueMetalDiago180Sprite;
    renderizables[ID_BLOQUE_DIAGONAL_270] = &bloqueMetalDiago270Sprite;
    renderizables[ID_PORTAL_AZUL] = &portalAzulSprite;
    renderizables[ID_PORTAL_NARANJA] = &portalNaranjaSprite;
    renderizables[ID_BOTON_APAGADO] = &botonSprite;
    renderizables[ID_COMPUERTA_CERRADA] = &compuertaCerradaSprite;
    renderizables[ID_COMPUERTA_ABRIENDO] = &compuertaAbriendoSprite;
    renderizables[ID_COMPUERTA_ABIERTA] = &compuertaAbiertaSprite;
    renderizables[ID_ROCA] = &piedra_sprite1;
    renderizables[ID_BOTON_PRENDIDO] = &botonPrendidoSprite;
    renderizables[ID_EMISORARRIBA] = &emisor_arriba_sprite;
    renderizables[ID_EMISORDERECHA] = &emisor_derecha_sprite;
    renderizables[ID_EMISORABAJO] = &emisor_abajo_sprite;
    renderizables[ID_EMISORIZQUIERDA] = &emisor_izquierda_sprite;
    renderizables[ID_BOLAENERGIA] = &bola_energia_sprite;
    renderizables[ID_RECEPTORARRIBA_ACTIVADO] = &receptor_arriba_activado_sprite;
    renderizables[ID_RECEPTORARRIBA_DESACTIVADO] = &receptor_arriba_desactivado_sprite;
    renderizables[ID_RECEPTORDERECHA_ACTIVADO] = &receptor_derecha_activado_sprite;
    renderizables[ID_RECEPTORDERECHA_DESACTIVADO] = &receptor_derecha_desactivado_sprite;
    renderizables[ID_RECEPTORABAJO_ACTIVADO] = &receptor_abajo_activado_sprite;
    renderizables[ID_RECEPTORABAJO_DESACTIVADO] = &receptor_abajo_desactivado_sprite;
    renderizables[ID_RECEPTORIZQUIERDA_ACTIVADO] = &receptor_izquierda_activado_sprite;
    renderizables[ID_RECEPTORIZQUIERDA_DESACTIVADO] = &receptor_izquierda_desactivado_sprite;
    renderizables[ID_ACIDO] = &acido_sprite;
    renderizables[ID_BARRAENERGIA] = &barra_energia_sprite;

    std::string musica_path("assets/sonidos/musica_juego.wav");
    Musica musica_portal(musica_path);
    musica_portal.setearVolumen(MIX_MAX_VOLUME / 5);
    Mix_AllocateChannels(16);

	std::string bg_path = "assets/industrial-background.jpg";
	Textura background(bg_path, ventana);
	Camera camara(ancho_nivel, alto_nivel, background);

	CoordConverter coord_converter(ancho_nivel, ancho_nivel);
	ColaBloqueante<Input> cola_input;
	ObtenedorInput obtenedor_input(coord_converter, camara, cola_input, ventana);
	//Renderizables renderizables(ventana);

	// Conexion con servidor.
	std::string host = "localhost";
	std::string port = "8080";
	Skt skt(host, port);
	skt.conectar();

	Mensajero mensajero_opcion(skt);
	Protocolo protocolo_opcion(mensajero_opcion);

	// ...
	// ELEGIR NUEVA PARTIDA O UNIRSE A PARTIDA
	// ...

	std::cout << "Presionar 'n' para crear la partida\n";
    std::cout << "O presionar 'u' para unirse a la partida ya creada\n";
    char tecla;
    std::cin >> tecla;
    std::string puerto_partida;
    if (tecla == 'n') {
        puerto_partida = this->requestNuevaPartida(protocolo_opcion);
    }
    if (tecla == 'u'){
        puerto_partida = this->requestUnirsePartida(protocolo_opcion);
    }
    skt.cerrarCanales();
	skt.cerrarSocket();
	


	Skt skt_partida(host, puerto_partida);
	skt_partida.conectar();
    std::cout << "partida creada\n";

    Mensajero mensajero(skt_partida);
    Protocolo protocolo(mensajero);
	// ...
	int id = protocolo.recibirId();
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
			coord_converter);

	th_input.start();
	th_renderizado.start();
	bool seguir = true;
    musica_portal.reproducirEnLoop();
	Timer capTimer;
	while(seguir) {
		//capTimer.start();
	    seguir = obtenedor_input.obtenerInput();
		renderizador.renderizar();
		int frameTicks = capTimer.getTicks();
		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
	//skt.cerrarCanales();
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
    // CASO UNIRSE A PARTIDA:
    protocolo.enviarOpcionUnirsePartida();
    std::string puerto_partida("8081");
    return puerto_partida;
}
