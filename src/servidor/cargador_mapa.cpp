
#include "config.h"
#include "angulo_dos_setenta.h"
#include <iostream>
#include "ids.h"
#include "cargador_mapa.h"
#include "estado_logico.h"
#include "boton.h"
#include "and.h"

#include "yaml-cpp/yaml.h"
#include "or.h"
#include "path.h"

CargadorMapa::CargadorMapa():
		gravedad(0, config.gravedad),
		mundo(gravedad),
		fisica(mundo){
	mundo.setContactListener(listener);
}


void CargadorMapa::cargarMapa(std::string& nombre_mapa) {
    std::string path_mapas = MAPAS;
	int id, identificador, x, y;
	std::string ruta_mapa = path_mapas + "mapas/" + nombre_mapa;
	YAML::Node archivo = YAML::LoadFile(ruta_mapa);
	for (auto it = archivo["Bloques"].begin(); it != archivo["Bloques"].end(); ++it){
		id = (*it)["Id"].as<int>();
		identificador = (*it)["Identificador"].as<int>();
		x = (*it)["X"].as<int>();
		y = (*it)["Y"].as<int>();

		switch(id){
			//El bloque roca y el bloque metal se crean distintos, no se cual esta bien
			case(ID_BLOQUE_ROCA):
				posiciones.emplace_back(x, y);
				bloques_roca.emplace_back(id, mundo, posiciones.back());
                break;
			case(ID_BLOQUE_METAL):
				posiciones.emplace_back(x, y);
				bloques_metal.emplace_back(mundo, posiciones.back());
                break;
		    case(ID_SPAWNPOINT):
		        posiciones.emplace_back(x, y);
		        fisica.agregarPosChell(posiciones.back());
				break;
		    case(ID_EMISORABAJO):
                posiciones.emplace_back(x, y);
                emisores_abajo.emplace_back(mundo, posiciones.back());
                break;
            case(ID_EMISORARRIBA):
                posiciones.emplace_back(x, y);
                emisores_arriba.emplace_back(mundo, posiciones.back());
                break;
            case(ID_EMISORIZQUIERDA):
                posiciones.emplace_back(x, y);
                emisores_izquierda.emplace_back(mundo, posiciones.back());
                break;
            case(ID_EMISORDERECHA):
                posiciones.emplace_back(x, y);
                emisores_derecha.emplace_back(mundo, posiciones.back());
                break;
		    case(ID_BLOQUE_DIAGONAL_0):
		        posiciones.emplace_back(x, y);
		        angulos_cero.emplace_back();
		        bloques_diagonal.emplace_back(mundo, posiciones.back(), angulos_cero.back());
		        break;
            case(ID_BLOQUE_DIAGONAL_90):
                posiciones.emplace_back(x, y);
                angulos_noventa.emplace_back();
                bloques_diagonal.emplace_back(mundo, posiciones.back(), angulos_noventa.back());
                break;
            case(ID_BLOQUE_DIAGONAL_180):
                posiciones.emplace_back(x, y);
                angulos_ciento_ochenta.emplace_back();
                bloques_diagonal.emplace_back(mundo, posiciones.back(),
                                              angulos_ciento_ochenta.back());
                break;
            case(ID_BLOQUE_DIAGONAL_270):
                posiciones.emplace_back(x, y);
                angulos_dos_setenta.emplace_back();
                bloques_diagonal.emplace_back(mundo, posiciones.back(),
                                              angulos_dos_setenta.back());
                break;
		    case(ID_ACIDO):
		        posiciones.emplace_back(x, y - 0.5 + config.tam_acido_y);
		        acidos.emplace_back(mundo, posiciones.back());
                break;
		    case(ID_BARRAENERGIA):
		        posiciones.emplace_back(x, y - 0.5);
		        barras_de_energia.emplace_back(mundo, posiciones.back());
                break;
		    case(ID_ROCA):
		        posiciones.emplace_back(x, y);
		        rocas.emplace_back(mundo, posiciones.back());
		        break;
		    case(ID_BOTON_APAGADO): {
                posiciones.emplace_back(x, y - 0.5 + config.tam_base_boton_y + 0.06);
                std::unique_ptr<Cuerpo> b(new Boton(posiciones.back(), mundo));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(b)));

                compuertas_logicas[identificador] = std::move(estado);
                break;
            }
            case(ID_COMPUERTA_CERRADA): {
                posiciones.emplace_back(x, y - 0.5);
                std::unique_ptr<Compuerta> c(new Compuerta(posiciones.back(), mundo));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(c)));

                compuertas_logicas[identificador] = std::move(estado);

                break;
		    }
            case(ID_RECEPTORABAJO_DESACTIVADO): {
                posiciones.emplace_back(x, y);
                std::unique_ptr<ReceptorAbajo> b(new ReceptorAbajo(mundo, posiciones.back()));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(b)));

                compuertas_logicas[identificador] = std::move(estado);
                break;
            }
            case(ID_RECEPTORARRIBA_DESACTIVADO): {
                posiciones.emplace_back(x, y);
                std::unique_ptr<Cuerpo> b(new ReceptorArriba(mundo, posiciones.back()));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(b)));

                compuertas_logicas[identificador] = std::move(estado);
                break;
            }
            case(ID_RECEPTORIZQUIERDA_DESACTIVADO): {
                posiciones.emplace_back(x, y);
                std::unique_ptr<Cuerpo> b(new ReceptorIzquierda(mundo, posiciones.back()));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(b)));

                compuertas_logicas[identificador] = std::move(estado);
                break;
            }
            case(ID_RECEPTORDERECHA_DESACTIVADO): {
                posiciones.emplace_back(x, y);
                std::unique_ptr<Cuerpo> b(new ReceptorDerecha(mundo, posiciones.back()));
                std::shared_ptr<EstadoLogico> estado(new EstadoLogico(std::move(b)));

                compuertas_logicas[identificador] = std::move(estado);
                break;
            }
            case(ID_AND): {
                std::unique_ptr<And> a(new And());
                compuertas_logicas[identificador] = std::move(a);
                break;
            }
            case(ID_OR): {
                std::unique_ptr<Or> a(new Or());
                compuertas_logicas[identificador] = std::move(a);
                break;
            }
            case(ID_TORTA):{
                posiciones.emplace_back(x, y);
                tortas.emplace_back(mundo, posiciones.back());
            }

		}

	}
	for (auto it = archivo["Conexiones"].begin(); it != archivo["Conexiones"].end(); ++it){
	    int a = (*it)["A"].as<int>();
        int b = (*it)["B"].as<int>();

        compuertas_logicas[b]->agregar(compuertas_logicas[a]);
	}
}

Fisica &CargadorMapa::obtenerFisica() {
	return fisica;
}

CargadorMapa::~CargadorMapa() {
}


