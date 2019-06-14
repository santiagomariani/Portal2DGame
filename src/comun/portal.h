#ifndef PORTAL_H
#define PORTAL_H
#include "Box2D/Box2D.h"
#include "mundo.h"
#include "cuerpo.h"

class Portal : public Cuerpo {
    int id;
    Mundo &mundo;
    Portal *hermano;
    b2Body *cuerpo;
    float orientacion;
    b2Vec2 pos;
    b2Vec2 normal;
public:
    Portal(int identidad, Mundo &mundo);
    Portal(Portal&& otro);

    void conectar(Portal *otro);
    void establecer(b2Vec2& posicion, b2Vec2& normal_entrada);
	void activar();
	uint8_t getId() override;
	int32_t getAngle() override;
	const b2Vec2& getPosition() override;
	void teletransportar(b2Body* otro);
	void expulsar(b2Body* otro, float orientacion_otro);
	float getAnguloSalida();
	float getAnguloEntrada();
	void empezarContacto(Cuerpo* otro) override;
	~Portal() = default;
};

#endif //PORTAL_H
