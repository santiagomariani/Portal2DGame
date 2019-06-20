#include "servidor.h"
#include <string>
#include <iostream>
#include "config.h"

Config config;

int main(int argc, const char *argv[]){
	if (argc != 2){
		std::cout << "Para ejecutar el servidor usar: ";
		std::cout << "./portal_servidor <puerto>\n";
		return 1;
	}
    std::string puerto(argv[1]);
    Servidor servidor;
    servidor.iniciarMultiPartidas(puerto);
    return 0;
}
