#ifndef VISTA_H
#define VISTA_H

#include "estado_teclado.h"
#include "Protocolo.h"
#include "Timer.h"
#include "SdlWindow.h"
#include "Camera.h"
#include <map>


class Vista{
	EstadoTeclado teclado;
	Protocolo& protocolo;
	Timer fpsTimer;
	Timer capTimer;
	SdlWindow& ventana;
	Camera& camara;
	std::map<int, Renderable*> texturas;
public:
	Vista(SdlWindow& ventana, Camera& camara, Protocolo& protocolo, 
		std::map<int, Renderable*> texturas);
	bool obtenerInput(CoordConverter& coordConverter);
	void renderizar();
	~Vista() = default;	
};

#endif
