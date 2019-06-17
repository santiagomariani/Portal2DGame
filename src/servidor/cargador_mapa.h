
#ifndef CARGADOR_MAPA_H
#define CARGADOR_MAPA_H

#include <list>

#include <contact_listener.h>
#include <mundo.h>
#include <angulo.h>
#include <bloque.h>
#include <bloque_metal.h>
#include <bloque_metal_diagonal.h>
#include <bloque_roca.h>
#include <roca.h>
#include <angulo_cero.h>
#include <angulo_ciento_ochenta.h>
#include <angulo_noventa.h>
#include "angulo_dos_setenta.h"
#include "receptor_arriba.h"
#include "receptor_abajo.h"
#include "receptor_izquierda.h"
#include "receptor_derecha.h"
#include "compuerta_logica.h"
#include "compuerta.h"
#include "emisor_arriba.h"
#include "emisor_abajo.h"
#include "emisor_izquierda.h"
#include "emisor_derecha.h"
#include "acido.h"
#include "barra_de_energia.h"
#include "fisica.h"

// Clase encargada de cargar y guardar un mapa dese un archivo yaml

class CargadorMapa {
    std::string nombre_mapa;

    b2Vec2 gravedad;
    Mundo mundo;
    ContactListener listener;
    Fisica fisica;

    std::vector<b2Vec2> posiciones; 
    // tal vez habria que cambiar los constructores de los cuerpos

    std::list<BloqueMetal> bloques_metal;
    std::list<BloqueRoca> bloques_roca;

    std::list<AnguloCero> angulos_cero;
    std::list<AnguloCientoOchenta> angulos_ciento_ochenta;
    std::list<AnguloDosSetenta> angulos_dos_setenta;
    std::list<AnguloNoventa> angulos_noventa;
    std::vector<BloqueMetalDiagonal> bloques_diagonal;
    std::list<Roca> rocas;

    std::map<int,std::unique_ptr<Cuerpo>> botones_y_receptores;
    std::map<int,std::shared_ptr<CompuertaLogica>> compuertas_logicas;

    std::list<Compuerta> compuertas;
    std::list<EmisorArriba> emisores_arriba;
    std::list<EmisorAbajo> emisores_abajo;
    std::list<EmisorIzquierda> emisores_izquierda;
    std::list<EmisorDerecha> emisores_derecha;
    std::list<Acido> acidos;
    std::list<BarraDeEnergia> barras_de_energia;

public:
    CargadorMapa();
    // Carga el mapa del archivo.
    void cargarMapa();
    // Devuelde la Fisica que se obtiene del mapa cargado.
    Fisica& obtenerFisica();
    ~CargadorMapa();
};


#endif //CARGADOR_MAPA_H
