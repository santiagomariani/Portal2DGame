#include "cursor.h"

Cursor::Cursor(std::map<int, Imagen*>& imagenes, int id) :
			   constructor(imagenes), id(id), imagenes(imagenes) {
}

void Cursor::setId(int _id){
	id = _id;
}

Pieza Cursor::actual(){
	return constructor.construir(id);
}

void Cursor::render(){
	imagenes[id]->render(actual_destino);
}

void Cursor::resetClick(){
	ultimo_click = -1;
	anteultimo_click = -1;
}

void Cursor::click(int identificador){
	anteultimo_click = ultimo_click;
	ultimo_click = identificador;
}
