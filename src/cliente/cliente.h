#ifndef CLIENTE_H
#define CLIENTE_H

#include "estado_teclado.h"
#include "protocolo.h"
#include "contador_tiempo.h"
#include "ventana.h"
#include "camara.h"
#include <map>


class Cliente{
public:
	Cliente() = default;
	void iniciar();
    std::string requestNuevaPartida(Protocolo &protocolo);
	std::string requestUnirsePartida(Protocolo &protocolo);
	~Cliente() = default;
};

#endif //CLIENTE_H
