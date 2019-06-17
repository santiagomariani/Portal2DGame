#ifndef CUERPO_H
#define CUERPO_H

#include "Box2D/Box2D.h"

class Cuerpo {
protected:
    float maxWidth;
    float maxHeight;
    Cuerpo(float maxWidth, float maxHeight) :
        maxWidth(maxWidth),
        maxHeight(maxHeight) {};
    Cuerpo() {};
public:
	// Devuelve id asociado al Cuerpo.
	virtual uint8_t getId() = 0;
	// Devuelve posicion asociada al Cuerpo.
	virtual const b2Vec2& getPosition() = 0;
	// Devuelve el angulo asociado al Cuerpo.
	virtual int32_t getAngle() {
	    return 0;
	}
	// Devuelve el maximo ancho posible.
	float getMaxWidth() {
        return maxWidth;
    }
    // Devuelve el maximo alto posible.
    float getMaxHeight() {
        return maxHeight;
    }
    ~Cuerpo() {};
	// Devuelve el b2Body asociado al cuerpo.
    virtual b2Body* getBody() {return nullptr;};
    // El cuerpo debera indicar que hacer en caso de que comienze contacto con
    // otro cuerpo.
	virtual void empezarContacto(Cuerpo* otro) = 0;
    // El cuerpo puede indicar que hacer en caso de que termine contacto con
    // otro cuerpo.
    virtual void terminarContacto(Cuerpo* otro) {}
    virtual void desactivar() {}
    virtual bool estaActivado() {return true;}
    // Aquellos cuerpos que se actualizen en cada 'step' deberan implementar
    // este metodo.
    virtual void actualizar() {}
};

#endif

