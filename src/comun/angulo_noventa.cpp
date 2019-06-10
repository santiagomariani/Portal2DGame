#include "angulo_noventa.h"
#include "Bloque.h"
#include "ids.h"
#include <iostream>
#include "config.h"
#define PI 3.14159265359

AnguloNoventa::AnguloNoventa(){
}

b2Vec2 AnguloNoventa::obtenerPosPortal(b2Vec2& dif_choque){
    if (dif_choque.x >= config::tam_bloque){
        std::cout << " derecha\n";
        return b2Vec2(config::tam_bloque, 0); //derecha
    }
    if (dif_choque.y <= -config::tam_bloque){
        return b2Vec2(0, -config::tam_bloque); // abajo
    }
    return b2Vec2(0, 0); // diagonal
}

b2Vec2 AnguloNoventa::obtenerNormalPortal(b2Vec2& dif_choque){
    if (dif_choque.x >= config::tam_bloque){
        return b2Vec2(1, 0);
    }
    if (dif_choque.y <= -config::tam_bloque){
        return b2Vec2(0, -1);
    }
    b2Vec2 normal(0, 1);
    b2Rot rotador(45*PI/180);
    return b2Mul(rotador, normal);
}


b2PolygonShape AnguloNoventa::obtenerTriangulo(){
    b2Vec2 vertices[3];
    vertices[0].Set(config::tam_bloque, -config::tam_bloque);
    vertices[1].Set(config::tam_bloque, config::tam_bloque);
    vertices[2].Set(-config::tam_bloque, -config::tam_bloque);
    b2PolygonShape polygonShape;
    polygonShape.Set(vertices, 3);

    return std::move(polygonShape);
}

int AnguloNoventa::getId(){
    return ID_BLOQUE_DIAGONAL_90;
}
