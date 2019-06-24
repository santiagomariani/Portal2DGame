#include "angulo_dos_setenta.h"
#include "bloque.h"
#include "ids.h"
#include "config.h"
#define PI 3.14159265359

AnguloDosSetenta::AnguloDosSetenta(){
}

b2Vec2 AnguloDosSetenta::obtenerPosPortal(b2Vec2& dif_choque){

    if (dif_choque.x <= -config.tam_bloque){
        return b2Vec2(-config.tam_bloque, 0); //izq
    }
    if (dif_choque.y >= config.tam_bloque){
        return b2Vec2(0, config.tam_bloque); // arriba
    }
    return b2Vec2(0, 0); // diagonal
}

b2Vec2 AnguloDosSetenta::obtenerNormalPortal(b2Vec2& dif_choque){
    if (dif_choque.x <= -config.tam_bloque){
        return b2Vec2(-1, 0);
    }
    if (dif_choque.y >= config.tam_bloque){
        return b2Vec2(0, 1);
    }
    b2Vec2 normal(0, -1);
    b2Rot rotador(45.0f*PI/180);
    return b2Mul(rotador, normal);
}

b2PolygonShape AnguloDosSetenta::obtenerTriangulo(){
    b2Vec2 vertices[3];
    vertices[0].Set(-config.tam_bloque, config.tam_bloque);
    vertices[1].Set(-config.tam_bloque, -config.tam_bloque);
    vertices[2].Set(config.tam_bloque, config.tam_bloque);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 3);

    return std::move(polygonShape);
}

int AnguloDosSetenta::getId(){
    return ID_BLOQUE_DIAGONAL_270;
}


b2Vec2 AnguloDosSetenta::obtenerVelocidadRebote(b2Vec2& vel_inicial){
    if (vel_inicial.x < 0){
        return b2Vec2(0, vel_inicial.x);
    }
    if (vel_inicial.y > 0){
        return b2Vec2(vel_inicial.y, 0);
    }
    return b2Vec2(vel_inicial.x * (-1), vel_inicial.y * (-1));
}

