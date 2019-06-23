#include "thread.h"
#include "protocolo.h"
#include "skt.h"

// Thread para recibir el id que envia el servidor al cliente cuando
// comienza la partida

class ThEsperarIdPartida : public Thread{
private:
	Protocolo& protocolo;
	Skt& skt;
	int* id;
	bool recibido;
public:
	ThEsperarIdPartida(Protocolo& protocolo, Skt& skt, int* id);
	void terminar() override;
	bool terminado();
    void run()  override;
	~ThEsperarIdPartida() = default;
};
