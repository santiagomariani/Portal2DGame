#ifndef PANTALLA_DATOS_CONEXION_H
#define PANTALLA_DATOS_CONEXION_H

#include <string>

class PantallaDatosConexion {
	std::string& puerto;
	std::string& host;

public:
	PantallaDatosConexion(std::string& puerto, std::string& host);

	// Devuelve si se debe continuar con el programa o no
	void operator()();
};

#endif //PANTALLA_DATOS_CONEXION_H
