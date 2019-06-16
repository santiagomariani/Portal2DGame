#include <map>
#include "SdlWindow.h"
#include "SdlTexture.h"
#include "Camera.h"
#include "Sprite.h"
#include "ViewChell.h"
#include "ids.h"
#include "Cliente.h"
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
