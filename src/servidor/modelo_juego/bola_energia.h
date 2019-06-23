
#ifndef BOLAENERGIA_H
#define BOLAENERGIA_H


#include <Box2D/Dynamics/b2Body.h>
#include "cuerpo.h"
#include "mundo.h"

#define DENSIDAD_BOLAENERGIA 1

class BolaEnergia : public Cuerpo {
private:
    b2Body *cuerpo;
    Mundo& mundo;
    const unsigned int TIEMPO_VIDA = 1000;
    unsigned int contador;
    bool finalizo;

public:
    BolaEnergia(Mundo &mundo, b2Vec2 &pos, b2Vec2 &dir_vel);
    BolaEnergia(BolaEnergia &&otro);
    BolaEnergia& operator=(BolaEnergia &&otro);

    // Actualiza el estado de la bola de energia
    // por si choco o no
    void actualizar() override;

    // Devuelve si la bola ya finalizo (tiene un tiempo de vida)
    bool bolaFinalizo();

    const b2Vec2& getPosition() override;

    int32_t getAngle() override;
    
    uint8_t getId() override;
    
    b2Body* getBody() override;
    
    // Avisa al mundo que se debe destruir la bola de energia
    void agregarCuerpoADestruir();
    
    void empezarContacto(Cuerpo *otro) override;

    void terminarContacto(Cuerpo *otro) override;
    
    // Quita a la bola del mundo (destruye el b2Body)
    void desactivar() override;
    
};

#endif //BOLAENERGIA_H
