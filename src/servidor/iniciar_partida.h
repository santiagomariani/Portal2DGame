#ifndef INICIAR_PARTIDA_H
#define INICIAR_PARTIDA_H

#include "partida.h"
#include "thread.h"

// iniciar partida cree la partida adentro. (puede recibir el skt y nombre del mapa)
// y partida tenga un mapa como atributo
// y al iniciar la partida cargue el mapa del archivo
// y el mapa tiene al mundo como atributo

class IniciarPartida : public Thread{
	Partida& partida;
public:
	IniciarPartida(Partida& partida);
    void run() override;
    void terminar() override;
	~IniciarPartida();

    void terminar_recibir_clientes();
};

#endif

