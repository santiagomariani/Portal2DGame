//
// Created by santi on 09/06/19.
//

#ifndef MAPARENDERIZABLES_H
#define MAPARENDERIZABLES_H


#include "Renderable.h"
#include "Ventana.h"
#include <map>

class Renderizables {
private:
    std::map<uint8_t, Renderable*> renderizales;
    void creacionRenderizables(Ventana &ventana);
public:
    explicit Renderizables(Ventana &ventana);
    Renderable * obtenerRenderizable(uint8_t id);
};


#endif //MAPARENDERIZABLES_H
