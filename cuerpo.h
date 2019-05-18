#ifndef CUERPO_H
#define CUERPO_H

class Cuerpo{
public:
	Cuerpo() {};
	virtual int getId() = 0;
	virtual const b2Vec2& getPosition() = 0;
	~Cuerpo() {};
};

#endif

