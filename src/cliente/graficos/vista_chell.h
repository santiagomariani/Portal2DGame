
#ifndef VISTA_CHELL_H
#define VISTA_CHELL_H

#include <SDL2/SDL_system.h>
#include <vector>
#include <map>

#include "textura.h"
#include "sprite.h"

class VistaChell : public Renderizable {
private:
    Textura textura_chell;
    std::map<uint8_t, Sprite> sprites;
    std::map<uint8_t, Sprite> sprites_transitorios;
    uint8_t estado_actual;
    bool renderizando_estado_transitorio;
    SDL_RendererFlip espejado_transitorio;
    double angulo_transitorio;
    SDL_Point *centro_transitorio;
    // Crea todos los Sprite y los guarda asociados c/u a un estado en el
    // mapa de sprites o el de sprites transitorios.
    void creacionSprites();

public:
    // Carga la textura y crea todos los sprites con la misma.
    VistaChell(Ventana &ventana, std::string nombre_archivo);
    VistaChell(VistaChell &&otro);
    VistaChell& operator=(VistaChell &&otro);
    // Renderiza el Sprite asociado con el estado actual. Si se esta
    // renderizando un estado transitorio (por ej. un disparo), el sprite se
    // renderiza con los parametros transitorios, los cuales son seteados al
    // cambiar estado.
    void renderizar(SDL_Rect &destino,
                    double angulo,
                    SDL_Point *centro,
                    SDL_RendererFlip espejado) override;
    // Actualiza el estado de la Chell. Si esta renderizando un estado
    // transitorio, entonces el estado actual no se actualiza. En caso
    // contrario si actualiza el estado, y ademas guarda los parametros
    // de renderizacion en el caso en el que el estado sea un estado
    // transitorio (disparo, salto, etc.).
    void cambiarEstado(uint8_t estado,
                       double angulo = 0,
                       SDL_Point *centro = nullptr,
                       SDL_RendererFlip espejado = SDL_FLIP_NONE);
    ~VistaChell() = default;
};


#endif //VISTA_CHELL_H
