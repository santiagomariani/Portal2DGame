#include "partida.h"

Partida::Partida(ColaProtegida& cola, Fisica& fisica): 
                    cola(cola), fisica(fisica){
    this->continuar_juego = true;
    this->recibir_clientes = true;
}

void Partida::correrPartida(){ // 
    while (this->continuar_juego){
        if (this->cola_input.estaVacia()){
            continue;
        }
        struct Input input = this->cola_input.pop();
        this->fisica.actualizar(input.teclado, input.mouse);

        std::vector<Cuerpo*> cuerpos = this->fisica.obtenerCuerpos();

        for (auto it=cuerpos.begin(); it!=cuerpos.end(); it++){
            for (auto c=colas_clientes.begin(); c!=colas_clientes.end(); c++){
                c->push(*it);
            }
        }
    }
    for (size_t i = 0; i < this->threads_clientes.size(); ++i){
        this->threads_clientes[i]->join();
        delete this->threads_clientes[i];
    }
}

void Partida::terminarPartida(){
    this->continuar_juego = false;
    for (auto it=threads_clientes.begin(); it!=threads_clientes.begin(); it++){
        it->terminar();
    }
}


int Partidas::recibirClientes(){ 
    std::vector<HeapProtected> colas_clientes;
    int i = 0;
    //while (this->recibir_clientes){
        try{
            Socket acept_skt = std::move(this->socket.aceptarClientes());

            colas_clientes.emplace_back();
            ProcesoCliente* proceso = new ProcesoCliente(
                                            std::move(acept_skt),
                                            this->cola_input.
                                            colas_clientes[i]);
            this->threads_clientes.push_back(proceso);

            proceso->start();

        } catch(const SocketError &e){
            if (!this->recibir_clientes){ // si no fue forzado
                std::cerr << "Error accepting client:\n";
                std::cerr << e.what();
            }
            break;
        }
        i++;
    //}
    return 0;
}

void Partida::terminarRecibirClientes(){
    this->recibir_clientes = false;
}
