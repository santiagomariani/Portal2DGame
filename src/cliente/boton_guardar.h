#ifndef BOTON_GUARDAR_H
#define BOTON_GUARDAR_H

#include "presionable.h"
#include "mapa_editor.h"
#include <string>

class BotonGuardar : public Presionable{
	MapaEditor& mapa;
	std::string& nombre;
public:
	BotonGuardar(Imagen* imagen, MapaEditor& mapa, std::string& nombre);
	void presionar() override;
};

#endif //BOTON_GUARDAR