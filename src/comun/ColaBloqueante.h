//
// Created by santi on 09/06/19.
//

#ifndef COLABLOQUEANTE_H
#define COLABLOQUEANTE_H

#include <queue>
#include <condition_variable>

template<class T>
class ColaBloqueante {
private:
    std::queue<T> cola;
    std::mutex m;
    std::condition_variable cond_var;
    bool done;
    bool notified;
public:
    ColaBloqueante() : done(false), notified(false) {
    }

    ColaBloqueante(ColaBloqueante&& otra){
        cola = std::move(otra.cola);
        m = std::move(otra.m);
        cond_var = std::move(otra.cond_var);
        done = otra.done;
        notified = otra.notified;

        otra.done = true;
        otra.notified = false;
    }
    // Encola y notifica a un thread para que este
    // desencole.
    void push(T elemento) {
        std::unique_lock<std::mutex> lock(m);
        cola.push(std::move(elemento));
        notified = true;
        cond_var.notify_one();
    }

    // Espera a poder desencolar . Si puede desencolar, devuelve
    // T. En caso de no haber mas nada para desencolar
    // se devuelve nullptr.
    bool pop(T &elemento) {
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
    void finalizado() {
        std::unique_lock<std::mutex> lock(this->m);
        done = true;
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
    bool done;
    bool notified;
public:
    ColaBloqueante() : done(false), notified(false) {
    }

    void push(void *elemento) {
        std::unique_lock<std::mutex> lock(m);
        cola.push(elemento);
        notified = true;
        cond_var.notify_one();
    }
    bool pop(void **elemento) {
        std::unique_lock<std::mutex> lock(m);
        while(true) {
            while (!notified && !done) {
                cond_var.wait(lock);
            }
            if (!cola.empty()) {
                *elemento = cola.front();
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
    void finalizado() {
        std::unique_lock<std::mutex> lock(this->m);
        done = true;
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
        done = otra.done;
        notified = otra.notified;

        otra.done = true;
        otra.notified = false;
    }
    void push(T *elemento) {
        ColaBloqueante<void*>::push(elemento);
    }
    bool pop(T **elemento) {
        void *aux;
        ColaBloqueante<void*>::pop(&aux);
        *elemento = (T*) aux;
    }

};

#endif //COLABLOQUEANTE_H
