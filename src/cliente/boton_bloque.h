#ifndef BOTON_BLOQUE_H
#define BOTON_BLOQUE_H

#include "presionable.h"
#include "cursor.h"

class BotonBloque : public Presionable{
	Cursor& cursor;
	int id;
public:
	BotonBloque(Cursor& cursor, int id, Imagen* imagen);

	// Llena el cursor con los datos del bloque que representa
	void presionar() override;

	// Cambia su posicion en pantalla
	void mover(int offset_x, int offset_y);
};

#endif //BOTON_BLOQUE