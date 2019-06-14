#include "cola_bloqueante_cuerpos.h"

ColaBloqueanteCuerpos::ColaBloqueanteCuerpos() : done(false), notified(false) {
}

// Encola y notifica a un thread para que este
// desencole.
void ColaBloqueanteCuerpos::push(CuerpoAEnviar elemento) {
    std::unique_lock<std::mutex> lock(m);
    cola.push(std::move(elemento));
    notified = true;
    cond_var.notify_one();
}

// Espera a poder desencolar . Si puede desencolar, devuelve
// T. En caso de no haber mas nada para desencolar
// se devuelve nullptr.
bool ColaBloqueanteCuerpos::pop(CuerpoAEnviar& elemento) {

    std::unique_lock<std::mutex> lock(m);
    while(true) {
        while (!notified && !done) {
            cond_var.wait(lock);
        }
        if (!cola.empty()) {
            elemento = std::move(cola.front());
            cola.pop();
            return true;
        }
        if (done) {
            return false;
        } else {
            this->notified = false;
        }
    }
}
// Se notifica a todos los threads que ya
// no hay mas nada para desencolar.
void ColaBloqueanteCuerpos::finalizado() {
    std::unique_lock<std::mutex> lock(this->m);
    done = true;
    cond_var.notify_all();
}

