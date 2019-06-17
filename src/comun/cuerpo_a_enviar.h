#ifndef CUERPO_A_ENVIAR_H
#define CUERPO_A_ENVIAR_H

#include "info_cuerpo_box_2_d.h"

struct CuerpoAEnviar {
	InfoCuerpoBox2D info_cuerpo;
	// Indica si es el ultimo cuerpo (para saber cuando renderizar todo junto).
	bool ultimo;
};

#endif //CUERPO_A_ENVIAR_H
