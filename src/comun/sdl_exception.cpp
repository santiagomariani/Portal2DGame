#include <string>
#include <SDL2/SDL_image.h>

#include "SdlException.h"

SdlException::SdlException(const char* descripcion, const char* error_sdl)
    : std::exception(), descripcion(descripcion) {
    this->descripcion.append("\n SDL_ERROR: ").append(error_sdl);
}

const char* SdlException::what() const noexcept{
    return this->descripcion.c_str();
}
