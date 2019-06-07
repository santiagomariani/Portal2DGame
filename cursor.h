#ifndef CURSOR_H
#define CURSOR_H

struct Cursor{ //Por default empieza con la roca normal...
	int ancho;
	int alto;
	int id;
	Cursor(int id, int ancho, int alto) :
		   ancho(ancho), alto(alto), id(id) {}
};


#endif //CURSOR