#ifndef SDL_EXCEPTION_H
#define SDL_EXCEPTION_H

#include <string>
#include <exception>

// Excepcion para los errores relacionados con SDL.
class SdlException : public std::exception {
private:
    std::string descripcion;

public:
    SdlException(const char *descripcion, const char *error_sdl);
    const char* what() const noexcept;
};

#endif //SDL_EXCEPTION_H
