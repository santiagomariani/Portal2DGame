#ifndef BOTON_BLOQUE_H
#define BOTON_BLOQUE_H

#include "presionable.h"
#include "cursor.h"

class BotonBloque : public Presionable{
	Cursor& cursor;
	int id;
	int ancho;
	int alto;
public:
	BotonBloque(Cursor& cursor, int id, int ancho, int alto, Imagen* imagen);
	void presionar() override;
	void mover(int offset_x, int offset_y);
};

#endif //BOTON_BLOQUE