#ifndef __SDL_TEXTURE_H__
#define __SDL_TEXTURE_H__

#include <string>

#include "Ventana.h"

class Textura {
private:
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    SDL_Texture* loadTexture(const std::string &filename);
    int width;
    int height;
public:
    Textura();
    // Crea un SDL_Texture, lanza una excepción si el filename es inválido.
    Textura(const std::string &filename, const Ventana &window);
    // Constructor por movimiento.
    Textura(Textura &&other);
    // Asignacion por movimiento.
    Textura& operator=(Textura &&other);
    // No es copiable.
    Textura(const Textura &other) = delete;
    Textura& operator=(const Textura &other) = delete;
    // Renderiza la textura cargada. Ademas puede rotar y espejar la imagen.
    int render(const SDL_Rect *src = nullptr,
               const SDL_Rect *dest = nullptr,
               double angle = 0.0,
               SDL_Point *center = nullptr,
               SDL_RendererFlip flip = SDL_FLIP_NONE) const;
    int getWidth();
    int getHeight();
    void setearColorModulacion(uint8_t r, uint8_t g, uint8_t b);
    // Libera la memoria reservada por la textura.
    ~Textura();
};

#endif
