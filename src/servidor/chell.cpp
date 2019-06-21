#include <iostream>
#include "chell.h"
#include "pistola.h"
#include "Box2D/Box2D.h"
#include "ids.h"
#include "ids_teclas.h"
#include "config.h"

#define TAMANIO_SENSOR_CHELL_X 0.001
#define TAMANIO_SENSOR_CHELL_Y 0.02
#define RADIO 0.15833f

Chell::Chell(int identidad, Mundo& mundo) :
        Cuerpo(config.tam_chell_x*2, config.tam_chell_y*2 + RADIO),
        id(identidad),
        pistola(mundo),
        mundo(mundo),
        roca(nullptr),
        joint_roca(nullptr),
        sensor(new SensorChell()) {
	cuerpo = nullptr;
}

void Chell::activar(b2Vec2& pos){
    if (cuerpo){
        mundo.destruirBody(cuerpo);
        cuerpo = nullptr;
    }
    b2BodyDef cuerpo_def;
    cuerpo_def.type = b2_dynamicBody;
    cuerpo_def.position.Set(pos.x, pos.y);
    cuerpo_def.fixedRotation = true;
    cuerpo_def.linearDamping = 0.006;
    cuerpo_def.gravityScale = config.escala_gravedad_chell;
    cuerpo = mundo.agregarBody(cuerpo_def);

    b2PolygonShape polygonShape;
    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape;
    myFixtureDef.density = 1; 
    myFixtureDef.friction = 0; 
    myFixtureDef.restitution = 0;

    b2Vec2 pos_poligono(0, 0.125f); // posicion del centro del poligono
    polygonShape.SetAsBox(config.tam_chell_x, config.tam_chell_y, pos_poligono, 0);
    cuerpo->CreateFixture(&myFixtureDef);

    b2CircleShape circulo;
    b2FixtureDef circulo_fix_def;
    circulo_fix_def.shape = &circulo;
    circulo_fix_def.density = 7;
    circulo_fix_def.friction = 0.1;
    circulo_fix_def.restitution = 0;

    circulo.m_p.Set(0, -2*RADIO); // posicion del centro del circulo
    circulo.m_radius = RADIO;
    cuerpo->CreateFixture(&circulo_fix_def);

    b2PolygonShape sensor_shape;
    b2FixtureDef sensor_fix_def;
    sensor_fix_def.shape = &sensor_shape;
    sensor_fix_def.isSensor = true;
    sensor_fix_def.userData = sensor.get();
    b2Vec2 pos_sensor(0, -3*RADIO - TAMANIO_SENSOR_CHELL_Y);
    sensor_shape.SetAsBox(TAMANIO_SENSOR_CHELL_X,
            TAMANIO_SENSOR_CHELL_Y,
            pos_sensor,
            0);
    cuerpo->CreateFixture(&sensor_fix_def);

    cuerpo->SetUserData(this);
}
uint8_t Chell::getId(){
    return ID_CHELL;
}

Chell::Chell(Chell&& otro) :
        Cuerpo(config.tam_chell_x*2, config.tam_chell_y*2 + RADIO),
        pistola(std::move(otro.pistola)),
        mundo(otro.mundo),
        estado_chell(std::move(otro.estado_chell)){
    if (this == &otro){
        return;
    }
    maxWidth = otro.maxWidth;
    maxHeight = otro.maxHeight;
    cuerpo = otro.cuerpo;
    roca = otro.roca;
    joint_roca = otro.joint_roca;
    sensor = std::move(otro.sensor);
    id = otro.id;

    otro.maxWidth = 0;
    otro.maxHeight = 0;
    otro.cuerpo = nullptr;
    otro.roca = nullptr;
    otro.joint_roca = nullptr;
	if (cuerpo){
		cuerpo->SetUserData(this);
	}
}


void Chell::mover(EstadoTeclado& t){
    if (!cuerpo){
        return;
    }
    b2Vec2 vel = cuerpo->GetLinearVelocity();
    float32 tecla = config.velocidad_chell * t.presionada(DERECHA) 
                    + -config.velocidad_chell * t.presionada(IZQUIERDA);
    if (tecla == 0){
        if (abs(vel.x) < 0.2) {
            vel.x = 0;
        } else if (vel.x < 0){
            vel.x +=0.2;
        } else if (vel.x > 0){
            vel.x -=0.2;
        }
    } else {
        vel.x = tecla;
    }

    if (sensor->estaActivado() && t.presionada(ARRIBA)) {
        vel.y = config.salto_chell * t.presionada(ARRIBA);
        if (roca && joint_roca) {
            b2Vec2 vel_roca = roca->getBody()->GetLinearVelocity();
            vel_roca.y = vel.y;
            roca->getBody()->SetLinearVelocity(vel_roca);
        }
    }
    cuerpo->SetLinearVelocity(vel);
    estado_chell.actualizarEstado(*sensor, vel);
}

const b2Vec2& Chell::getPosition(){
    return cuerpo->GetPosition();
}

void Chell::dispararAzul(b2Vec2& pos_click){
    if (!cuerpo){
        return;
    }
    pistola.dispararAzul(getPosition(), pos_click);
    estado_chell.ocurrioDisparo();
}

void Chell::dispararNaranja(b2Vec2& pos_click){
    if (!cuerpo){
        return;
    }
    pistola.dispararNaranja(getPosition(), pos_click);
    estado_chell.ocurrioDisparo();
}

float Chell::getWidth(){
    return float(config.tam_chell_x * 2);
}
float Chell::getHeight(){
    return float(config.tam_chell_y * 2 + 0.25);
}

b2Body* Chell::getBody(){
	return cuerpo;
}

void Chell::agarrarRoca(EstadoTeclado &t) {
    if ((t.presionada(TECLA_E)) && (roca != nullptr)) {
        if (joint_roca == nullptr) {
            b2Vec2 nueva_pos_roca(
                    this->getPosition().x + config.tam_chell_x + (roca->getMaxWidth() / 2),
                    this->getPosition().y);
            roca->getBody()->SetTransform(nueva_pos_roca, 0);
            b2DistanceJointDef joint_def;
            joint_def.Initialize(this->getBody(),
                                 roca->getBody(),
                                 this->getPosition(),
                                 roca->getPosition());
            joint_def.collideConnected = true;
            joint_def.frequencyHz = 10;
            joint_def.dampingRatio = 1;
            joint_roca = (getBody()->GetWorld())->CreateJoint(&joint_def);
        } else {
            getBody()->GetWorld()->DestroyJoint(joint_roca);
            joint_roca = nullptr;
        }
    }
}

void Chell::empezarContacto(Cuerpo* otro){
    if (otro->getId() == ID_BLOQUE_METAL){
    }
    if ((otro->getId() == ID_ROCA) && (roca == nullptr)) {
        roca = (Roca*)otro;
    }
}

void Chell::terminarContacto(Cuerpo *otro) {
    if (otro->getId() == ID_ROCA && !joint_roca) {
        roca = nullptr;
    }
}

void Chell::morir(){
    estado_chell.chellMurio();
    mundo.agregarCuerpoADestruir(this);
}

void Chell::destruirRoca() {
    if (roca && joint_roca) {
        mundo.agregarJointADestruir(joint_roca);
        joint_roca = nullptr;
        roca->resetear();
        roca = nullptr;
    }
}

uint8_t Chell::obtenerEstado() {
    return estado_chell.obtenerEstado();
}

uint8_t Chell::obtenerOrientacion() {
    return estado_chell.obtenerOrientacion();
}

int Chell::getIdPersonaje() {
    return id;
}

void Chell::desactivar() {
    if (this->cuerpo){
        mundo.destruirBody(this->cuerpo);
        this->cuerpo = nullptr;
    }
}

void Chell::ganar(){
    if (this->cuerpo){
        //this->cuerpo->SetActive(false);
    }
    this->estado_chell.chellGano();
}
