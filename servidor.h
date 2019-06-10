#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

class Servidor{
public:
	Servidor(std::string puerto);
	void iniciar();
	~Servidor();
};

#endif

