
#ifndef COLA_PROTEGIDA_H
#define COLA_PROTEGIDA_H

#include <input.h>
#include <queue>
#include <mutex>

// Cola protegida que guarda structs Input.

class ColaProtegidaInput {
private:
    std::queue<Input> cola;
    std::mutex m;
public:
    ColaProtegidaInput();

    // Encola y notifica a un thread para que este
    // desencole.
    void push(Input elemento);

    // Espera a poder desencolar . Si puede desencolar, devuelve
    // T. En caso de no haber mas nada para desencolar
    // se devuelve nullptr.
    bool pop(Input& elemento);

    ~ColaProtegidaInput() = default;
};


#endif
