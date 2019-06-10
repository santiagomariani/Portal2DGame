#ifndef INICIAR_PARTIDA_H
#define INICIAR_PARTIDA_H

#include "partida.h"
#include "Thread.h"

class IniciarPartida : public Thread{
	Partida& partida;
public:
	IniciarPartida(Partida& partida);
    void run() override;
    void terminar() override;
	~IniciarPartida();
};

#endif

