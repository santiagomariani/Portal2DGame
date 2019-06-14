//
// Created by santi on 18/05/19.
//

#include <SDL2/SDL_timer.h>
#include "Timer.h"

Timer::Timer() : startTicks(0),
    pausedTicks(0),
    started(false),
    paused(false) {
}

void Timer::start() {
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop() {
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause() {
    if (started && !paused) {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unPause() {
    if (started && paused) {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

uint32_t Timer::getTicks() {
    uint32_t time = 0;
    if (started) {
        if (paused) {
            time = pausedTicks;
        } else {
            time = SDL_GetTicks() - startTicks;
        }
    }
    return time;
}
