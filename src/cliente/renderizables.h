
#ifndef MAPARENDERIZABLES_H
#define MAPARENDERIZABLES_H


#include "Renderizable.h"
#include "Ventana.h"
#include <map>

class Renderizables {
private:
    std::map<uint8_t, Renderizable*> renderizales;
    void creacionRenderizables(Ventana &ventana);
public:
    explicit Renderizables(Ventana &ventana);
    Renderizable * obtenerRenderizable(uint8_t id);
};


#endif //MAPARENDERIZABLES_H
