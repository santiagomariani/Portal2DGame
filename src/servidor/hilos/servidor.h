#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <string>

class Servidor{
public:
	Servidor();
	void iniciarMultiPartidas(std::string puerto);
	~Servidor();
};

#endif

