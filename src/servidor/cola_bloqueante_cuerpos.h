#ifndef COLA_BLOQUEANTE_CUERPOS_H
#define COLA_BLOQUEANTE_CUERPOS_H

#include <queue>
#include <condition_variable>
#include "cuerpo.h"
#include "cuerpo_a_enviar.h"

class ColaBloqueanteCuerpos {
private:
    std::queue<CuerpoAEnviar> cola;
    std::mutex m;
    std::condition_variable cond_var;
    bool done;
    bool notified;
public:
    ColaBloqueanteCuerpos();
    // Encola y notifica a un thread para que este desencole.
    void push(CuerpoAEnviar elemento);
    // Espera a poder desencolar . Si puede desencolar, devuelve true. En caso
    // de no haber mas nada para desencolar devuelve false.
    bool pop(CuerpoAEnviar& elemento);
    // Se notifica a todos los threads que ya no hay mas nada para desencolar.
    void finalizado();
    ~ColaBloqueanteCuerpos() = default;
};

#endif //COLA_BLOQUEANTE_CUERPOS_H
