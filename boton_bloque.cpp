#include "boton_bloque.h"

BotonBloque::BotonBloque(Cursor& cursor, int id, int ancho,
						int alto, Imagen* imagen) : cursor(cursor),
						id(id), ancho(ancho), alto(alto),
						Presionable(imagen) {
}
void BotonBloque::presionar(){
	cursor.ancho = ancho;
	cursor.alto = alto;
	cursor.id = id;
}

void BotonBloque::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}
