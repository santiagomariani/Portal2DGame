//
// Created by seba on 11/06/19.
//

#ifndef INFO_CUERPO_BOX_2_D_H
#define INFO_CUERPO_BOX_2_D_H


#include <cstdint>
#include <Box2D/Common/b2Math.h>

struct InfoCuerpoBox2D {
    uint8_t id;
    uint8_t estado;
    uint8_t orientacion;
    int32_t angulo;
    b2Vec2 pos;
    float32 ancho;
    float32 alto;
};


#endif //INFO_CUERPO_BOX_2_D_H
