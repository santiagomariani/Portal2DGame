#include "Cliente.h"
#include "estado_mouse.h"
#include "CoordConverter.h"
#include "ViewChell.h"
#include "InfoCuerpo.h"
#include "ids.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_image.h>
#include "Box2D/Box2D.h"
#include "ObtenedorInput.h"
#include "Renderizador.h"
#include "ColaBloqueante.h"
#include "Input.h"
#include "ThInput.h"
#include "Skt.h"
#include "ThRenderizado.h"

void Cliente::iniciar() {
	const int screen_width = 800;
	const int screen_height = 600;

	SdlWindow ventana(screen_width, screen_height);

	std::string bg_path = "assets/industrial-background.jpg";
	SdlTexture background(bg_path, ventana);
	Camera camara(screen_width, screen_height, background);

	CoordConverter coord_converter(screen_width, screen_width);
	ColaBloqueante<Input> cola_input;
	ObtenedorInput obtenedor_input(coord_converter, camara, cola_input);
	Renderizables renderizables(ventana);

	// Conexion con servidor.
	std::string host = "localhost";
	std::string port = "8080";
	Skt skt(host, port);
	skt.conectar();

	Mensajero mensajero(skt);
	Protocolo protocolo(mensajero);
	ThInput th_input(cola_input, protocolo);

	ColaBloqueante<InfoCuerpo> cola_renderizado;

	Renderizador renderizador(ventana,
			camara,
			cola_renderizado,
			renderizables);

	ThRenderizado th_renderizado(cola_renderizado,
			protocolo,
			renderizador,
			coord_converter);

	th_input.start();
	th_renderizado.start();
	bool terminado = false;
	Timer capTimer;
	while(!terminado) {
		capTimer.start();
	    terminado = obtenedor_input.obtenerInput();
		renderizador.renderizar();
		int frameTicks = capTimer.getTicks();
		if (frameTicks < TICKS_PER_FRAME) {
			SDL_Delay(TICKS_PER_FRAME - frameTicks);
		}
	}
	th_renderizado.terminar();
	th_renderizado.join();
	th_input.terminar();
	th_input.join();
}
