#include "servidor.h"
#include <string>
#include "config.h"

Config config;

int main(int argc, const char *argv[]){
    std::string puerto("8080");
    Servidor servidor;
    servidor.iniciarMultiPartidas(puerto);
}
