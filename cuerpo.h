#ifndef CUERPO_H
#define CUERPO_H

class Cuerpo{
protected:
    float maxWidth;
    float maxHeight;
    Cuerpo(float maxWidth, float maxHeight) :
        maxWidth(maxWidth),
        maxHeight(maxHeight) {};
public:
	virtual int getId() = 0;
	virtual const b2Vec2& getPosition() = 0;
	float getMaxWidth() {
        return maxWidth;
    }
    float getMaxHeight() {
        return maxHeight;
    }
    ~Cuerpo() {};
};

#endif

