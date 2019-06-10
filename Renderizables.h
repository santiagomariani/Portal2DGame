//
// Created by santi on 09/06/19.
//

#ifndef MAPARENDERIZABLES_H
#define MAPARENDERIZABLES_H


#include "Renderable.h"
#include "SdlWindow.h"
#include <map>

class Renderizables {
private:
    std::map<uint8_t, Renderable*> renderizales;
    void creacionRenderizables(SdlWindow &ventana);
public:
    explicit Renderizables(SdlWindow &ventana);
    Renderable * obtenerRenderizable(uint8_t id);
};


#endif //MAPARENDERIZABLES_H
