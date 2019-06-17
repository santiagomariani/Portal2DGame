#include "fondo_continuo.h"

FondoContinuo::FondoContinuo(int ancho_f, int alto_f, int ancho_v, int alto_v,
							 int velocidad, Textura& textura) :
				  			 ancho_f(ancho_f), alto_f(alto_f),
				  			 ancho_v(ancho_v), alto_v(alto_v),
				  			 velocidad(velocidad), textura(textura){
	area.x = 0;
	area.y = 0;
	area.w = ancho_f;
	area.h = alto_f;
	ventana.x = 0;
	ventana.y = 0;
	ventana.w = ancho_v;
	ventana.h = alto_v;
}
void FondoContinuo::render(){
	textura.renderizar(&area, &ventana);
	area.x += velocidad;
	if (area.x + area.w >= textura.obtenerAncho()){
		area.x = 0;
	}
}