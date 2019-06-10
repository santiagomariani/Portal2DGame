#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

class Servidor{
public:
	Servidor();
	void iniciar(std::string puerto);
	~Servidor();
};

#endif

