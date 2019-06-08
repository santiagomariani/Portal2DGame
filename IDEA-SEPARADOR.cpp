
struct render_info{
	int id;
	int estado;
	SDL_Rect destino;
	double angulo;
	SDL_Renderflip flip;
};
//

void protocolo.enviar_cuerpo(Cuerpo* cuerpo); // serializa y se lo guarda en un vector de int
struct render_info protocolo.recibir_cuerpo(); // desserializar vector de ints y crea el sctructct

void protocolo.enviar_teclado(EstadoTeclado& t, EstadoMouse& m); // serializa y se guarda en vector de ints
void protocolo.recibir_teclado(EstadoTeclado& t, EstadoMouse& m); // deserializa y setea los t y m

//


while(running){
	running = Vista.poll_event_teclado_SDL(); //cliente enviar teclado
	Fisica.actualizar_fisica() // servidor recibir teclado
	Fisica.fisica_enviar_cuerpos(); // servidor enviar cuerpo
	Vista.renderizar() // Cliente recibir cuerpos
}



bool poll_event_teclado_SDL(Protocolo& protocolo){
	EstadoTeclado teclado; // guardar como atributo o recibir
	EstadoMouse mouse;
	SDL_Event event;
	seguir = true;
	while (SDL_PollEvent(&event) != 0){
		switch(event.type) {
			case SDL_KEYDOWN:{
				SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
				teclado.agregar_evento(keyEvent);
				break;
			}
			case SDL_KEYUP:{
				SDL_KeyboardEvent& keyEvent = (SDL_KeyboardEvent&) event;
				teclado.agregar_evento(keyEvent);
				break;
			}
			case SDL_MOUSEBUTTONDOWN:{
				SDL_MouseButtonEvent& mouseEvent = (SDL_MouseButtonEvent&) event;
				if ((mouseEvent.button) == SDL_BUTTON_LEFT){
					mouse.agregarClickIzquierdo(mouseEvent.x, mouseEvent.y);
				}
				if ((mouseEvent.button) == SDL_BUTTON_RIGHT){
					b2Vec2 click = coordConverter.sdlToBox2D(mouseEvent.x, mouseEvent.y, camera); // camara???
					mouse.agregarClickDerecho(click);
				}
				break;
			}
			case SDL_QUIT:
				seguir = false;
		}	
	}
	protocolo.enviarTeclado(teclado, mouse);
	return seguir;
}

void actualizar_fisica(){ // guardar mundo y chell(personajes) como atributo
	EstadoTeclado teclado;
	EstadoMouse mouse;
	protocolo.recibirTeclado(teclado, mouse);

	chell.agarrarRoca(teclado);
	chell.mover(teclado);
	if (mouse.clickDerecho()){
		b2Vec2 click = mouse.posClickDerecho();
		chell.dispararNaranja(click);
	}
	if (mouse.clickIzquierdo()){
		b2Vec2 click = mouse.posClickIzquierdo();
		chell.dispararAzul(click);
	}
	mundo.actualizar();
}

void fisica_enviar_cuerpos(){
	//Chell& chell = personajes.obtener_chell(id);
	b2Body *cuerpos = mundo.obtenerBodies();
	while (cuerpos){
		Cuerpo *actual = (Cuerpo*)cuerpos->GetUserData();
		if (!actual){
			cuerpos = cuerpos->GetNext();
			continue;
		}
		protocolo.enviarCuerpo(actual)
		cuerpos = cuerpos->GetNext();
	}
}


void renderizar(){
	fpsTimer.start(); // fpsTimer guardar como atributo
	window.fill(0x33, 0x33, 0x33, 0xFF); // guardar window
	struct cuerpo_info;
	bool hay_cuerpo = protocolo.recibirCuerpo(cuerpo_info);
	camera.renderBg(); // guardar camara
	camera.updateCamera(cuerpo_info->destino); // tiene que ser la chell del cliente
	while (hay_cuerpo){
		struct cuerpo_info;
		bool hay_cuerpo = protocolo.recibirCuerpo(cuerpo_info);

		SDL_Rect dest = cuerpo_info->destino;
		int id = cuerpo_info->id;
		int estado = cuerpo_info->estado;
		double angulo = cuerpo_info->angulo;
		if (id == ID_DISPARO) {
			camera.render(*texturas[id], dest, angulo); // guardar texturas
		} else if (id == ID_PORTAL_AZUL || id == ID_PORTAL_NARANJA){
			camera.render(*texturas[id], dest, angulo);
		} else if (id == ID_BOLAENERGIA) {
			camera.render(*texturas[id], dest, angulo);
		} else if (id == ID_CHELL) {
			((ViewChell*)texturas[id])->cambiarEstado(estado);

			// ORIENTACION DE CHELL 
			/*uint8_t orientacion_actual_chell = ((Chell*)actual)->obtenerOrientacion();
			if (orientacion_actual_chell == CHELL_MIRA_IZQ) {
				camera.render(*texturas[id], dest, 0, nullptr, SDL_FLIP_HORIZONTAL);


			}*/ else {
				camera.render(*texturas[id], dest);
			}
		} else {
			camera.render(*texturas[id], dest);
		}
	}
	window.render();

	int frameTicks = capTimer.getTicks(); // guardar capTimer como atributo
	if (frameTicks < TICKS_PER_FRAME) {
		SDL_Delay(TICKS_PER_FRAME - frameTicks);
	}
}


