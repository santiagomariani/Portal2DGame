

#include "cola_protegida.h"

ColaProtegidaInput::ColaProtegidaInput(){
}


void ColaProtegidaInput::push(Input elemento) {
    std::unique_lock<std::mutex> lock(m);
    cola.push(std::move(elemento));
}

bool ColaProtegidaInput::pop(Input& elemento) {
    std::unique_lock<std::mutex> lock(m);
    if (!cola.empty()) {
        elemento = std::move(cola.front());
        cola.pop();
        return true;
    }
    return false;
}


