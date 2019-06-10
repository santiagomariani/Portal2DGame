#ifndef VISTA_H
#define VISTA_H

#include "estado_teclado.h"
#include "Protocolo.h"
#include "Timer.h"
#include "SdlWindow.h"
#include "Camera.h"
#include <map>


class Cliente{
private:
public:
	// Cliente(SdlWindow& ventana, Camera& camara, Protocolo& protocolo,
	//	std::map<int, Renderable*> texturas);
	Cliente() = default;
	void iniciar();
	~Cliente() = default;
};

#endif
