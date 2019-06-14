
#ifndef CARGADOR_MAPA_H
#define CARGADOR_MAPA_H

#include <list>

#include <contact_listener.h>
#include <mundo.h>
#include <angulo.h>
#include <Bloque.h>
#include <BloqueMetal.h>
#include <bloque_metal_diagonal.h>
#include <BloqueRoca.h>
#include <Roca.h>
#include <angulo_cero.h>
#include <angulo_ciento_ochenta.h>
#include <angulo_noventa.h>
#include "angulo_dos_setenta.h"
#include "ReceptorArriba.h"
#include "ReceptorAbajo.h"
#include "ReceptorIzquierda.h"
#include "ReceptorDerecha.h"
#include "compuerta_logica.h"
#include "compuerta.h"
#include "EmisorArriba.h"
#include "EmisorAbajo.h"
#include "EmisorIzquierda.h"
#include "EmisorDerecha.h"
#include "Acido.h"
#include "BarraDeEnergia.h"
#include "fisica.h"

class CargadorMapa {
    std::string nombre_mapa;

    b2Vec2 gravedad;
    Mundo mundo;
    ContactListener listener;
    Fisica fisica;

    std::vector<b2Vec2> posiciones; // tal vez habria que cambiar los constructores de los cuerpos

    std::list<BloqueMetal> bloques_metal;
    std::list<BloqueRoca> bloques_roca;

    std::list<AnguloCero> angulos_cero;
    std::list<AnguloCientoOchenta> angulos_ciento_ochenta;
    std::list<AnguloDosSetenta> angulos_dos_setenta;
    std::list<AnguloNoventa> angulos_noventa;
    std::vector<BloqueMetalDiagonal> bloques_diagonal;
    std::list<Roca> rocas;

    std::map<int,Cuerpo*> botones_y_receptores;

    /*std::map<int,ReceptorAbajo> receptores_abajo;
    std::map<int,ReceptorIzquierda> receptores_izquierda;
    std::map<int,ReceptorDerecha> receptores_derecha;*/

    std::map<int,CompuertaLogica*> compuertas_logicas;

    std::list<Compuerta> compuertas;
    std::list<EmisorArriba> emisores_arriba;
    std::list<EmisorAbajo> emisores_abajo;
    std::list<EmisorIzquierda> emisores_izquierda;
    std::list<EmisorDerecha> emisores_derecha;
    std::list<Acido> acidos;
    std::list<BarraDeEnergia> barras_de_energia;

public:
    CargadorMapa();
    void cargarMapa();
    Fisica& obtenerFisica();
    ~CargadorMapa();
};


#endif //CARGADOR_MAPA_H
