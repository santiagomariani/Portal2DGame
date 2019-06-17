
#ifndef COLA_BLOQUEANTE_H
#define COLA_BLOQUEANTE_H

#include <queue>
#include <condition_variable>

template<class T>
class ColaBloqueante {
private:
    std::queue<T> cola;
    std::mutex m;
    std::condition_variable cond_var;
    bool terminado;
    bool notificado;
public:
    ColaBloqueante() : terminado(false), notificado(false) {
    }

    // Constructor por movimiento.
    ColaBloqueante(ColaBloqueante&& otra){
        cola = std::move(otra.cola);
        m = std::move(otra.m);
        cond_var = std::move(otra.cond_var);
        terminado = otra.terminado;
        notificado = otra.notificado;

        otra.terminado = true;
        otra.notificado = false;
    }
    // Encola y notifica a un thread para que este desencole.
    void push(T elemento) {
        std::unique_lock<std::mutex> lock(m);
        cola.push(std::move(elemento));
        notificado = true;
        cond_var.notify_one();
    }

    // Espera a poder desencolar . Si puede desencolar, devuelve true. En caso
    // de no haber mas nada para desencolar devuelve false.
    bool pop(T &elemento) {
        std::unique_lock<std::mutex> lock(m);
        while(true) {
            while (!notificado && !terminado) {
                cond_var.wait(lock);
            }
            if (!cola.empty()) {
                elemento = cola.front();
                cola.pop();
                return true;
            }
            if (terminado) {
                return false;
            } else {
                this->notificado = false;
            }
        }
    }
    // Se notifica a todos los threads que ya no hay mas nada para desencolar.
    void finalizado() {
        std::unique_lock<std::mutex> lock(this->m);
        terminado = true;
        cond_var.notify_all();
    }

    ~ColaBloqueante() = default;
};

template<>
class ColaBloqueante<void*> {
private:
    std::queue<void*> cola;
    std::mutex m;
    std::condition_variable cond_var;
    bool terminado;
    bool notificado;
public:
    ColaBloqueante() : terminado(false), notificado(false) {
    }

    void push(void *elemento) {
        std::unique_lock<std::mutex> lock(m);
        cola.push(elemento);
        notificado = true;
        cond_var.notify_one();
    }
    bool pop(void **elemento) {
        std::unique_lock<std::mutex> lock(m);
        while(true) {
            while (!notificado && !terminado) {
                cond_var.wait(lock);
            }
            if (!cola.empty()) {
                *elemento = cola.front();
                cola.pop();
                return true;
            }
            if (terminado) {
                return false;
            } else {
                this->notificado = false;
            }
        }
    }
    void finalizado() {
        std::unique_lock<std::mutex> lock(this->m);
        terminado = true;
        cond_var.notify_all();
    }
    ~ColaBloqueante() = default;
};

template<class T>
class ColaBloqueante<T*> : public ColaBloqueante<void*> {
public:
    ColaBloqueante(): ColaBloqueante<void*>(){
    }
    ColaBloqueante(ColaBloqueante&& otra){
        cola = std::move(otra.cola);
        m = std::move(otra.m);
        cond_var = std::move(otra.cond_var);
        terminado = otra.done;
        notificado = otra.notified;

        otra.done = true;
        otra.notified = false;
    }
    void push(T *elemento) {
        ColaBloqueante<void*>::push(elemento);
    }
    bool pop(T **elemento) {
        void *aux;
        bool resul = ColaBloqueante<void*>::pop(&aux);
        *elemento = (T*) aux;
        return resul;
    }

};

#endif //COLA_BLOQUEANTE_H
