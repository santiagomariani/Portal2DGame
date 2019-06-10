#include "servidor.h"
#include <string>

int main() {
    std::string puerto("8080");
    Servidor servidor;
    servidor.iniciar(puerto);
}
