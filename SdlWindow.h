#ifndef __SDL_WINDOW_H__
#define __SDL_WINDOW_H__

#include <cstdint>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_system.h>

class SdlWindow {
private:
    int width;
    int height;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    SdlWindow(int width, int height);
    void fill(uint8_t r, uint8_t g, uint8_t b, uint8_t alpha);
    void fill();
    void render();
    SDL_Renderer* getRenderer() const;
    ~SdlWindow();
};

#endif
