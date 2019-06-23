
#include "cargar_configuracion.h"
#include "yaml-cpp/yaml.h"
#include "config.h"

void CargarConfiguracion::operator()(std::string& nombre){
	YAML::Node archivo = YAML::LoadFile(nombre);
	config.gravedad = archivo["gravedad"].as<float>();
	config.escala_gravedad_chell = archivo["escala gravedad chell"].as<float>();
	config.velocidad_chell = archivo["velocidad chell"].as<float>();
	config.salto_chell = archivo["salto chell"].as<float>();
	config.radio_disparo = archivo["radio disparo"].as<float>();
	config.velocidad_disparo = archivo["velocidad disparo"].as<float>();
	config.radio_bola_energia = archivo["radio bola energia"].as<float>();
	config.vel_bola_energia = archivo["velocidad bola energia"].as<float>();
}
