#include "boton_guardar.h"
#include "skt.h"
#include "mensajero.h"
#include "protocolo.h"
#include <fstream>
#include <iostream>

BotonGuardar::BotonGuardar(Imagen* imagen, MapaEditor& mapa, std::string& nombre) : 
						   Presionable(imagen), mapa(mapa), nombre(nombre){
}
void BotonGuardar::presionar(){
	std::string host = "localhost";
	std::string port = "8080";
	Skt skt(host, port);
	skt.conectar();
	Mensajero mensajero(skt);
	Protocolo protocolo(mensajero);
	protocolo.enviarOpcionCrearMapa();
	protocolo.enviarNombreMapa(nombre);
	std::string mapa_yaml = mapa.guardar();
	std::cout << mapa_yaml << std::endl;
	protocolo.enviarMapa(mapa_yaml);
}