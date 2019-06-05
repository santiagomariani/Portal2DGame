#ifndef CURSOR_H
#define CURSOR_H

struct Cursor{ //Por default empieza con la roca normal...
	int ancho;	//El ancho esta contado en Celdas
	int alto;	//El alto esta contado en Celdas
	int id;
	Cursor(int id, int ancho, int alto) :
		   ancho(ancho), alto(alto), id(id) {}
};


#endif //CURSOR