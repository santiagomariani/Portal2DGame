#include <map>
#include "ventana.h"
#include "textura.h"
#include "camara.h"
#include "sprite.h"
#include "vista_chell.h"
#include "ids.h"
#include "cliente.h"
#include "editor.h"
#include "inicio.h"
#include "config.h"

Config config;

int main(int argc, const char *argv[]){

    Cliente cliente;

	int etapa = 0;
	bool juego = true;
	while (juego){
		switch (etapa){
			case(0):
				Inicio i;
				i(&etapa);
				break;
			case(1):
				Editor e;
				e(&etapa);
				break;
			case(2):
			    cliente.iniciar(&etapa);
				break;
			case(3):
				juego = false;
				break;
		}
	}

	//Cliente cliente;
	//cliente.iniciar();
}
