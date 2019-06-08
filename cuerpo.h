#ifndef CUERPO_H
#define CUERPO_H

#include "Box2D/Box2D.h"

class Cuerpo{
protected:
    float maxWidth;
    float maxHeight;
    Cuerpo(float maxWidth, float maxHeight) :
        maxWidth(maxWidth),
        maxHeight(maxHeight) {};
    Cuerpo() {};
public:
	virtual uint8_t getId() = 0;
	virtual const b2Vec2& getPosition() = 0;
	virtual int32_t getAngle() {
	    return 0;
	}
	float getMaxWidth() {
        return maxWidth;
    }
    float getMaxHeight() {
        return maxHeight;
    }
    ~Cuerpo() {};
    virtual b2Body* getBody() {};
	virtual void empezarContacto(Cuerpo* otro) = 0;
    virtual void terminarContacto(Cuerpo* otro) {}
    virtual void desactivar() {}
    virtual bool estaActivado() {return true;}
    virtual void actualizar() {}
};

#endif

