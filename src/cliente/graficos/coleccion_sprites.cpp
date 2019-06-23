
#include "coleccion_sprites.h"
#include "ventana.h"
#include "ids.h"
#include "textura.h"
#include "sprite.h"
#include "vista_chell.h"

ColeccionSprites::ColeccionSprites(Ventana &ventana) {
    creacionSprites(ventana);
}

void ColeccionSprites::creacionSprites(Ventana &ventana) {

    // TEXTURA EFECTOS

    std::string arch_textura_efectos = "assets/fx.png";
    texturas.emplace_back(arch_textura_efectos,ventana);
    // Disparo.
    sprites.insert(std::make_pair(ID_DISPARO,
            Sprite(111, 59, 1, 1920, 3, texturas.back())));

    // Rocas.
    sprites.insert(std::make_pair(ID_ROCA,
            Sprite(85, 83, 1, 4513, 1, texturas.back())));
    /*
    Sprite sprite_piedra2(85, 83, 87, 4513, 1, textura_efectos);
    Sprite sprite_piedra3(85, 83, 173, 4513, 1, textura_efectos);
    Sprite sprite_piedra4(85, 83, 259, 4513, 1, textura_efectos);
    Sprite sprite_piedra5(85, 83, 345, 4513, 1, textura_efectos);
    Sprite sprite_piedra6(85, 83, 431, 4513, 1, textura_efectos);
    Sprite sprite_piedra7(85, 83, 517, 4513, 1, textura_efectos);
    Sprite sprite_piedra8(85, 83, 603, 4513, 1, textura_efectos);
    */

    // Bola de energia.
    sprites.insert(std::make_pair(ID_BOLAENERGIA,
            Sprite(171, 119, 1, 2000, 5, texturas.back())));

    // TEXTURA BLOQUES

    std::string arch_textura_bloques = "assets/blocks1.png";
    texturas.emplace_back(arch_textura_bloques, ventana);

    // Bloques roca y metal.

    // Bloque roca.
    sprites.insert(std::make_pair(ID_BLOQUE_ROCA,
            Sprite(193, 193, 1, 172, 1, texturas.back())));
    // Bloque metal.
    sprites.insert(std::make_pair(ID_BLOQUE_METAL,
            Sprite(193, 193, 1, 600, 1, texturas.back())));

    // EmisorArriba.
    sprites.insert(std::make_pair(ID_EMISORARRIBA,
            Sprite(193, 193, 1, 1242, 1, texturas.back())));
    // EmisorDerecha.
    sprites.insert(std::make_pair(ID_EMISORDERECHA,
            Sprite(193, 193, 1, 1028, 1, texturas.back())));
    // EmisorAbajo.
    sprites.insert(std::make_pair(ID_EMISORABAJO,
            Sprite(193, 193, 1, 1456, 1, texturas.back())));
    // EmisorIzquierda.
    sprites.insert(std::make_pair(ID_EMISORIZQUIERDA,
            Sprite(193, 193, 1, 814, 1, texturas.back())));

    // Receptores.

    // ReceptorArriba.
    // 	Activado.
    sprites.insert(std::make_pair(ID_RECEPTORARRIBA_ACTIVADO,
            Sprite(192, 192, 466, 1243, 1, texturas.back())));
    // Desactivado.
    sprites.insert(std::make_pair(ID_RECEPTORARRIBA_DESACTIVADO,
            Sprite(192, 192, 233, 1243, 1, texturas.back())));

    // ReceptorDerecha.
    // 	Activado.
    sprites.insert(std::make_pair(ID_RECEPTORDERECHA_ACTIVADO,
            Sprite(192, 192, 465, 1029, 1, texturas.back())));
    // Desactivado.
    sprites.insert(std::make_pair(ID_RECEPTORDERECHA_DESACTIVADO,
            Sprite(192, 192, 235, 1029, 1, texturas.back())));

    // ReceptorIzquierda.
    // 	Activado.
    sprites.insert(std::make_pair(ID_RECEPTORIZQUIERDA_ACTIVADO,
            Sprite(192, 192, 464, 814, 1, texturas.back())));
    // Desactivado.
    sprites.insert(std::make_pair(ID_RECEPTORIZQUIERDA_DESACTIVADO,
            Sprite(192, 192, 235, 814, 1, texturas.back())));

    // ReceptorAbajo.
    // 	Activado.
    sprites.insert(std::make_pair(ID_RECEPTORABAJO_ACTIVADO,
            Sprite(192, 192, 468, 1457, 1, texturas.back())));
    // Desactivado.
    sprites.insert(std::make_pair(ID_RECEPTORABAJO_DESACTIVADO,
            Sprite(192, 192, 232, 1457, 1, texturas.back())));

    // TEXTURA BLOQUE DIAG 0
    std::string arch_textura_bloque_diag_0 = "assets/block-diago.png";
    texturas.emplace_back(arch_textura_bloque_diag_0, ventana);
    // Bloque diagonal 0°.
    sprites.insert(std::make_pair(ID_BLOQUE_DIAGONAL_0,
            Sprite(178, 177, 0, 2, 1, texturas.back())));
    // TEXTURA BLOQUE DIAG 90°
    std::string arch_textura_bloque_diag_90 = "assets/diago-90.png";
    texturas.emplace_back(arch_textura_bloque_diag_90, ventana);
    // Bloque diagonal 90°.
    sprites.insert(std::make_pair(ID_BLOQUE_DIAGONAL_90,
            Sprite(177, 178, 2, 0, 1, texturas.back())));
    // TEXTURA BLOQUE DIAG 180°
    std::string arch_textura_bloque_diag_180 = "assets/diago-180.png";
    texturas.emplace_back(arch_textura_bloque_diag_180, ventana);
    // Bloque diagonal 180°.
    sprites.insert(std::make_pair(ID_BLOQUE_DIAGONAL_180,
            Sprite(177, 178, 2, 0, 1, texturas.back())));
    // TEXTURA BLOQUE DIAG 270°
    std::string arch_textura_bloque_diag_270 = "assets/diago-270.png";
    texturas.emplace_back(arch_textura_bloque_diag_270, ventana);
    sprites.insert(std::make_pair(ID_BLOQUE_DIAGONAL_270,
            Sprite(177, 178, 2, 0, 1, texturas.back())));

    // TEXTURA VARIOS
    std::string arch_textura_varios = "assets/miscellaneous.png";
    texturas.emplace_back(arch_textura_varios, ventana);

    // Boton apagado y prendidos.
    // Boton apagado
    sprites.insert(std::make_pair(ID_BOTON_APAGADO,
            Sprite(175, 55, 1, 116, 1, texturas.back())));
    // Boton prendido
    sprites.insert(std::make_pair(ID_BOTON_PRENDIDO,
            Sprite(175, 74, 1, 192, 1, texturas.back())));

    // Acido.
    sprites.insert(std::make_pair(ID_ACIDO,
            Sprite(300, 61, 1, 1545, 8, texturas.back())));

    // Barra Energia.
    sprites.insert(std::make_pair(ID_BARRAENERGIA,
            Sprite(8, 220, 528, 689, 1, texturas.back())));

    // TEXTURA COMPUERTA
    std::string arch_textura_compuerta = "assets/gate.png";
    texturas.emplace_back(arch_textura_compuerta, ventana);

    // Compuerta cerrada.
    sprites.insert(std::make_pair(ID_COMPUERTA_CERRADA,
            Sprite(193, 385, 1, 21, 1, texturas.back())));

    // Compuerta abierta.
    //                                textura_compuerta);
    sprites.insert(std::make_pair(ID_COMPUERTA_ABIERTA,
            Sprite(193, 385, 1553, 2437, 1, texturas.back())));
    // Compuerta abriendo.
    // textura_compuerta);
    sprites.insert(std::make_pair(ID_COMPUERTA_ABRIENDO,
            Sprite(193, 385, 1, 2051, 19, texturas.back())));



    // TEXTURA PORTAL AZUL
    std::string arch_textura_portal_azul = "assets/portAzul.png";
    texturas.emplace_back(arch_textura_portal_azul, ventana);
    // Portal azul.
    sprites.insert(std::make_pair(ID_PORTAL_AZUL,
            Sprite(193, 193, 0, 0, 1, texturas.back())));

    // TEXTURA PORTAL NARANJA
    std::string arch_textura_portal_naranja = "assets/portNaranja.png";
    texturas.emplace_back(arch_textura_portal_naranja, ventana);
    // Portal naranja.
    sprites.insert(std::make_pair(ID_PORTAL_NARANJA,
            Sprite(193, 193, 0, 0, 1, texturas.back())));


    // TEXTURA TORTA
    std::string arch_textura_torta = "assets/torta.png";
    texturas.emplace_back(arch_textura_torta, ventana);
    // Torta.
    sprites.insert(std::make_pair(ID_TORTA,
            Sprite(381, 389, 0, 0, 1, texturas.back())));
}

Sprite & ColeccionSprites::obtenerSprite(uint8_t id) {
    return sprites.at(id);
}
