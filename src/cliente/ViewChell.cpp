//
// Created by santi on 17/05/19.
//

#include <iostream>
#include "ViewChell.h"

#define CHELL_EN_EL_AIRE 0
#define CHELL_MOVIENDOSE 1
#define CHELL_QUIETA 2
#define CHELL_CAMBIA_ORIENTACION 3

/*
#define FIREIDLETOREST 3
#define JIG 4
#define SWEAT 5
#define RUNSHOOT 6
#define SHOOT 7
#define STOP 8
#define SPIKED 9
#define TURN 10
#define JUMPFIRE 11
#define IDLE 12
#define FLYINGHORZ 13
#define FIRE 14
#define FLYING 15
#define JUMPRISE 16
#define JUMPLAND 17
#define ENTERHOLD 18
#define JUMPFALL 19
#define SMASHED 20
#define ENTER 21
#define DIE 22
*/

ViewChell::ViewChell(SdlWindow &window) : renderizando_estado_transitorio(false) {
    std::string shootingPath = "assets/chelltextures.png";
    chellTextures = std::move(SdlTexture(shootingPath, window));
    spritesCreation();
}

void ViewChell::spritesCreation() {
    // JumpApex
    sprites.insert(std::make_pair(CHELL_EN_EL_AIRE,
            Sprite(137, 207, 1, 21, 1, chellTextures)));
    // Run
    sprites.insert(std::make_pair(CHELL_MOVIENDOSE,
                                  Sprite(194, 204, 1, 4123, 12, chellTextures)));
    // RestingIdle
    sprites.insert(std::make_pair(CHELL_QUIETA,
                                  Sprite(104, 215, 1, 2073, 7, chellTextures)));
    // Turn
    sprites.insert(std::make_pair(CHELL_CAMBIA_ORIENTACION,
                                  Sprite(192, 203, 1, 3223, 8, chellTextures)));

    estado_actual = CHELL_QUIETA;
    /*
    // FireIdleToRest
    sprites.emplace_back(143, 213, 1, 1104, 4, chellTextures);
    // Jig
    sprites.emplace_back(168, 243, 1, 6609, 79, chellTextures);
    // Sweat
    sprites.emplace_back(215, 225, 1, 4993, 13, chellTextures);
    // RunShoot
    sprites.emplace_back(194, 209, 1, 4553, 12, chellTextures);
    // Stop
    sprites.emplace_back(165, 215, 1, 3671, 12, chellTextures);
    // Spiked
    sprites.emplace_back(173, 203, 1, 3447, 9, chellTextures);
    // JumpFire
    sprites.emplace_back(188, 225, 1, 2977, 8, chellTextures);
    // Idle
    sprites.emplace_back(151, 202, 1, 2754, 7, chellTextures);
    // FlyingHorz
    sprites.emplace_back(215, 191, 1, 2542, 4, chellTextures);
    // Fire
    sprites.emplace_back(170, 212, 1, 2309, 5, chellTextures);
    // Flying
    sprites.emplace_back(144, 229, 1, 1338, 4, chellTextures);
    // JumpRise
    sprites.emplace_back(143, 228, 1, 855, 4, chellTextures);
    // JumpLand
    sprites.emplace_back(230, 199, 1, 635, 2, chellTextures);
    // EnterHold
    sprites.emplace_back(164, 199, 1, 249, 1, chellTextures);
    // JumpFall
    sprites.emplace_back(156, 217, 1, 1835, 4, chellTextures);
    // Smashed
    sprites.emplace_back(210, 269, 1, 5465, 14, chellTextures);
    // Enter
    sprites.emplace_back(207, 281, 1, 6025, 16, chellTextures);
    // Die
    sprites.emplace_back(175, 261, 1, 8825, 72, chellTextures);
    */
}

void ViewChell::render(SDL_Rect &dest,
        double angle,
        SDL_Point *center,
        SDL_RendererFlip flip) {

    Sprite &sprite_actual = sprites.at(estado_actual);

    if (renderizando_estado_transitorio) {
        sprite_actual.render(dest,
                angulo_transitorio,
                centro_transitorio,
                flip_transitorio);
        if (sprite_actual.finalizoAnimacion()) {
            renderizando_estado_transitorio = false;
        }
    } else {
        sprite_actual.render(dest, angle, center, flip);
    }
}

void ViewChell::cambiarEstado(uint8_t estado,
        double angle, SDL_Point *center,
        SDL_RendererFlip flip) {
    if (!renderizando_estado_transitorio) {
        estado_actual = estado;
        // estado es un estado transitorio?
        if (estado == CHELL_CAMBIA_ORIENTACION) {
            renderizando_estado_transitorio = true;
            flip_transitorio = flip;
            angulo_transitorio = angle;
            centro_transitorio = center;
        }
    }
}
