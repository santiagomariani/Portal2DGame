#include "angulo_ciento_ochenta.h"
#include "Bloque.h"
#include "ids.h"
#define PI 3.14159265359

AnguloCientoOchenta::AnguloCientoOchenta(){
}

b2Vec2 AnguloCientoOchenta::obtenerPosPortal(b2Vec2& dif_choque){

    if (dif_choque.x >= TAMANIO_BLOQUE){
        return b2Vec2(TAMANIO_BLOQUE, 0); //derecha
    }
    if (dif_choque.y >= TAMANIO_BLOQUE){
        return b2Vec2(0, TAMANIO_BLOQUE); // arriba
    }
    return b2Vec2(0, 0); // diagonal
}

b2Vec2 AnguloCientoOchenta::obtenerNormalPortal(b2Vec2& dif_choque){
    if (dif_choque.x >= TAMANIO_BLOQUE){
        return b2Vec2(1, 0);
    }
    if (dif_choque.y >= TAMANIO_BLOQUE){
        return b2Vec2(0, 1);
    }
    b2Vec2 normal(-1, 0);
    b2Rot rotador(45.0f*PI/180);
    return b2Mul(rotador, normal);
}

b2PolygonShape AnguloCientoOchenta::obtenerTriangulo(){
    b2Vec2 vertices[3];
    vertices[0].Set(TAMANIO_BLOQUE, TAMANIO_BLOQUE);
    vertices[1].Set(-TAMANIO_BLOQUE, TAMANIO_BLOQUE);
    vertices[2].Set(TAMANIO_BLOQUE, -TAMANIO_BLOQUE);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 3);

    return std::move(polygonShape);
}

int AnguloCientoOchenta::getId(){
    return ID_BLOQUE_DIAGONAL_180;
}

