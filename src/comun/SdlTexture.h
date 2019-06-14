#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>

#include "SdlWindow.h"

class SdlTexture {
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Texture* loadTexture(const std::string &filename);
    int width;
    int height;
public:
    SdlTexture();
    // Crea un SDL_Texture, lanza una excepción si el filename es inválido.
    SdlTexture(const std::string &filename, const SdlWindow &window);
    // Constructor por movimiento.
    SdlTexture(SdlTexture &&other);
    // Asignacion por movimiento.
    SdlTexture& operator=(SdlTexture &&other);
    // No es copiable.
    SdlTexture(const SdlTexture &other) = delete;
    SdlTexture& operator=(const SdlTexture &other) = delete;
    // Renderiza la textura cargada. Ademas puede rotar y espejar la imagen.
    int render(const SDL_Rect *src = nullptr,
               const SDL_Rect *dest = nullptr,
               double angle = 0.0,
               SDL_Point *center = nullptr,
               SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    int getWidth();
    int getHeight();
    // Libera la memoria reservada por la textura.
    ~SdlTexture();
};

#endif
