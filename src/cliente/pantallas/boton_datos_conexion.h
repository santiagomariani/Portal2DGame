#ifndef BOTON_DATOS_CONEXION_H
#define BOTON_DATOS_CONEXION_H

#include "presionable.h"

class BotonDatosConexion : public Presionable{
	bool* corriendo;
public:
	BotonDatosConexion(Imagen* imagen, bool* corriendo);

	// Abre el modo jugar del juego
	void presionar() override;
};

#endif //BOTON_DATOS_CONEXION_H