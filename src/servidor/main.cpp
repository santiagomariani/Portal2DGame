#include "servidor.h"
#include <string>

int main(int argc, const char *argv[]){
    std::string puerto("8080");
    Servidor servidor;
    servidor.iniciar(puerto);
}
