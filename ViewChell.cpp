//
// Created by santi on 17/05/19.
//

#include <iostream>
#include "ViewChell.h"

#define FIREIDLETOREST 0
#define JIG 1
#define SWEAT 2
#define RUNSHOOT 3
#define SHOOT 4
#define STOP 5
#define SPIKED 6
#define TURN 7
#define JUMPFIRE 8
#define IDLE 9
#define FLYINGHORZ 10
#define FIRE 11
#define RESTINGIDLE 12
#define FLYING 13
#define JUMPRISE 14
#define JUMPLAND 15
#define ENTERHOLD 16
#define JUMPAPEX 17
#define JUMPFALL 18
#define SMASHED 19
#define ENTER 20
#define DIE 21

ViewChell::ViewChell(SdlWindow &window) {
    std::string shootingPath = "assets/chelltextures.png";
    chellTextures = std::move(SdlTexture(shootingPath, window));
    spritesCreation();
}

void ViewChell::spritesCreation() {
    // FireIdleToRest
    sprites.emplace_back(143, 213, 1, 1104, 4, chellTextures);
    // Jig
    sprites.emplace_back(168, 243, 1, 6609, 79, chellTextures);
    // Sweat
    sprites.emplace_back(215, 225, 1, 4993, 13, chellTextures);
    // RunShoot
    sprites.emplace_back(194, 209, 1, 4553, 12, chellTextures);
    // Run
    sprites.emplace_back(194, 204, 1, 4123, 12, chellTextures);
    // Stop
    sprites.emplace_back(165, 215, 1, 3671, 12, chellTextures);
    // Spiked
    sprites.emplace_back(173, 203, 1, 3447, 9, chellTextures);
    // Turn
    sprites.emplace_back(192, 203, 1, 3223, 8, chellTextures);
    // JumpFire
    sprites.emplace_back(188, 225, 1, 2977, 8, chellTextures);
    // Idle
    sprites.emplace_back(151, 202, 1, 2754, 7, chellTextures);
    // FlyingHorz
    sprites.emplace_back(215, 191, 1, 2542, 4, chellTextures);
    // Fire
    sprites.emplace_back(170, 212, 1, 2309, 5, chellTextures);
    // RestingIdle
    sprites.emplace_back(104, 215, 1, 2073, 7, chellTextures);
    // Flying
    sprites.emplace_back(144, 229, 1, 1338, 4, chellTextures);
    // JumpRise
    sprites.emplace_back(143, 228, 1, 855, 4, chellTextures);
    // JumpLand
    sprites.emplace_back(230, 199, 1, 635, 2, chellTextures);
    // EnterHold
    sprites.emplace_back(164, 199, 1, 249, 1, chellTextures);
    // JumpApex
    sprites.emplace_back(137, 207, 1, 21, 1, chellTextures);
    // JumpFall
    sprites.emplace_back(156, 217, 1, 1835, 4, chellTextures);
    // Smashed
    sprites.emplace_back(210, 269, 1, 5465, 14, chellTextures);
    // Enter
    sprites.emplace_back(207, 281, 1, 6025, 16, chellTextures);
    // Die
    sprites.emplace_back(175, 261, 1, 8825, 72, chellTextures);
    actualSprite = RESTINGIDLE;
}

void ViewChell::render(SDL_Rect &dest,
        double angle,
        SDL_Point *center,
        SDL_RendererFlip flip) {
    Sprite &sprite = sprites.at(actualSprite);
    sprite.render(dest, angle, center, flip);
}
