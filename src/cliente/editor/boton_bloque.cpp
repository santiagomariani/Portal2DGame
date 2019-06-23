#include "boton_bloque.h"

BotonBloque::BotonBloque(Cursor& cursor, int id, Imagen* imagen) :
						cursor(cursor), id(id), Presionable(imagen) {
}
void BotonBloque::presionar(){
	cursor.setId(id);
}

void BotonBloque::mover(int offset_x, int offset_y){
	destino.x += offset_x;
	destino.y += offset_y;
}
