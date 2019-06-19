
#include <iostream>
#include "vista_chell.h"
#include "estado_chell.h"

VistaChell::VistaChell(Ventana &ventana, std::string nombre_archivo) :
    renderizando_estado_transitorio(false),
    angulo_transitorio(0),
    centro_transitorio(nullptr),
    espejado_transitorio(SDL_FLIP_NONE),
    textura_chell(nombre_archivo, ventana) {
    creacionSprites();
}

void VistaChell::creacionSprites() {
    // JumpApex | Chell en el aire
    sprites.insert(std::make_pair(CHELL_EN_EL_AIRE,
            Sprite(137, 207, 1, 21, 1, textura_chell)));
    // Run | Chell corre
    sprites.insert(std::make_pair(CHELL_MOVIENDOSE,
                                  Sprite(194, 204, 1, 4123, 12,
                                          textura_chell)));

    // RestingIdle | Chell descansa
    sprites.insert(std::make_pair(CHELL_QUIETA,
                                  Sprite(104, 215, 1, 2073, 7,
                                          textura_chell)));
    // Turn | Chell se da vuelta
    sprites_transitorios.insert(std::make_pair(CHELL_CAMBIA_ORIENTACION,
                                  Sprite(192, 203, 1, 3223, 8,
                                          textura_chell)));
    // RunShoot | Chell se mueve y dispara.
    sprites_transitorios.insert(std::make_pair(CHELL_MOVIENDOSE_Y_DISPARA,
                                  Sprite(194, 209, 1, 4553, 12,
                                          textura_chell)));
    // Fire | Chell dispara quieta.
    sprites_transitorios.insert(std::make_pair(CHELL_QUIETA_Y_DISPARA,
                                  Sprite(170, 212, 1, 2309, 5,
                                          textura_chell)));
    // JumpFire | Chell dispara en el aire.
    sprites_transitorios.insert(std::make_pair(CHELL_EN_EL_AIRE_Y_DISPARA,
                                  Sprite(188, 225, 1, 2977, 8,
                                          textura_chell)));
    // JumpFall | Chell salta
    sprites_transitorios.insert(std::make_pair(CHELL_SALTA,
                                               Sprite(143, 228, 1, 855, 4,
                                                       textura_chell)));
    // Die | Chell muere.
    sprites_transitorios.insert(std::make_pair(CHELL_MUERE,
            Sprite(175, 261, 1, 8825, 72, textura_chell)));

    // Chell gana, llega a la torta.
    sprites.insert((std::make_pair(CHELL_GANO,
                                   Sprite(168, 243, 1, 6609, 79,
                                          textura_chell))));

    estado_actual = CHELL_QUIETA;
}

void VistaChell::renderizar(SDL_Rect &destino,
                           double angulo,
                           SDL_Point *centro,
                           SDL_RendererFlip espejado) {

    if ((estado_actual != CHELL_QUIETA) 
    && (estado_actual != CHELL_EN_EL_AIRE)
    && (estado_actual != CHELL_SALTA)) {
        destino.w *= 1.5;
    } else if (estado_actual == CHELL_EN_EL_AIRE) {
        destino.w *= 1.1;
    } else if (estado_actual == CHELL_SALTA) {
        destino.w *= 1.1;
    }

    if (renderizando_estado_transitorio) {
        Sprite &sprite_actual = sprites_transitorios.at(estado_actual);
        sprite_actual.renderizar(destino,
                                 angulo_transitorio,
                                 centro_transitorio,
                                 espejado_transitorio);
        if (sprite_actual.finalizoAnimacion()) {
            renderizando_estado_transitorio = false;
        }
    } else {
        Sprite &sprite_actual = sprites.at(estado_actual);
        sprite_actual.renderizar(destino, angulo, centro, espejado);
    }
}

void VistaChell::cambiarEstado(uint8_t estado,
        double angulo, SDL_Point *centro,
        SDL_RendererFlip espejado) {
    if (!renderizando_estado_transitorio) {
        estado_actual = estado;
        if (sprites_transitorios.count(estado)) {
            renderizando_estado_transitorio = true;
            espejado_transitorio = espejado;
            angulo_transitorio = angulo;
            centro_transitorio = centro;
        }
    }
}

VistaChell::VistaChell(VistaChell &&otro) {
    textura_chell = std::move(otro.textura_chell);
    otro.sprites.clear();
    otro.sprites_transitorios.clear();
    creacionSprites();

    estado_actual = otro.estado_actual;
    angulo_transitorio = otro.angulo_transitorio;
    centro_transitorio = otro.centro_transitorio;
    espejado_transitorio = otro.espejado_transitorio;
    renderizando_estado_transitorio = otro.renderizando_estado_transitorio;

    otro.estado_actual = CHELL_QUIETA;
    otro.angulo_transitorio = 0;
    otro.centro_transitorio = nullptr;
    otro.espejado_transitorio = SDL_FLIP_NONE;
    otro.renderizando_estado_transitorio = false;
}

VistaChell &VistaChell::operator=(VistaChell &&otro) {
    if (this == &otro) {
        return *this;
    }
    textura_chell = std::move(otro.textura_chell);
    otro.sprites.clear();
    otro.sprites_transitorios.clear();
    sprites.clear();
    sprites_transitorios.clear();
    creacionSprites();

    estado_actual = otro.estado_actual;
    angulo_transitorio = otro.angulo_transitorio;
    centro_transitorio = otro.centro_transitorio;
    espejado_transitorio = otro.espejado_transitorio;
    renderizando_estado_transitorio = otro.renderizando_estado_transitorio;

    otro.estado_actual = CHELL_QUIETA;
    otro.angulo_transitorio = 0;
    otro.centro_transitorio = nullptr;
    otro.espejado_transitorio = SDL_FLIP_NONE;
    otro.renderizando_estado_transitorio = false;
}
