//
// Created by santi on 09/06/19.
//

#include "Renderizables.h"
#include "SdlWindow.h"
#include "ids.h"
#include "SdlTexture.h"
#include "Sprite.h"
#include "ViewChell.h"

Renderizables::Renderizables(SdlWindow &ventana) {
    creacionRenderizables(ventana);
}

void Renderizables::creacionRenderizables(SdlWindow &ventana) {
    // Disparo
    std::string efectos_path = "assets/fx.png";
    SdlTexture efectos_textura(efectos_path, ventana);
    Sprite disparoSprite(111, 59, 1, 1920, 3, efectos_textura);

    // Bloques roca y metal
    std::string blocksPath = "assets/blocks1.png";
    SdlTexture blocksTexture(blocksPath, ventana);
    Sprite bloqueSprite(193, 193, 1, 172, 1, blocksTexture);
    Sprite bloqueMetalSprite(193, 193, 1, 600, 1, blocksTexture);
    std::string diago_path = "assets/block-diago.png";
    SdlTexture diago_texture(diago_path, ventana);
    Sprite bloqueMetalDiagoSprite(178, 177, 0, 2, 1, diago_texture);
    std::string diago90_path = "assets/diago-90.png";
    SdlTexture diago90_texture(diago90_path, ventana);
    Sprite bloqueMetalDiago90Sprite(177, 178, 2, 0, 1, diago90_texture);
    std::string diago180_path = "assets/diago-180.png";
    SdlTexture diago180_texture(diago180_path, ventana);
    Sprite bloqueMetalDiago180Sprite(177, 178, 2, 0, 1, diago180_texture);
    std::string diago270_path = "assets/diago-270.png";
    SdlTexture diago270_texture(diago270_path, ventana);
    Sprite bloqueMetalDiago270Sprite(177, 178, 2, 0, 1, diago270_texture);

    // Boton apagado y prendidos
    std::string botonPath = "assets/miscellaneous.png";
    SdlTexture miscTexture(botonPath, ventana);
    Sprite botonSprite(175, 55, 1, 116, 1, miscTexture);
    Sprite botonPrendidoSprite(175, 74, 1, 192, 1, miscTexture);

    // Compuerta cerrada y abierta
    std::string compuertaPath = "assets/gate.png";
    SdlTexture compuertaTexture(compuertaPath, ventana);
    Sprite compuertaCerradaSprite(193, 385, 1, 21, 1, compuertaTexture);
    Sprite compuertaAbiertaSprite(193, 385, 1553, 2437, 1, compuertaTexture);
    Sprite compuertaAbriendoSprite(193, 385, 1, 2051, 19, compuertaTexture);

    //Portal azul
    std::string portalAzulPath = "assets/portAzul.png";
    SdlTexture portalAzulTexture(portalAzulPath, ventana);
    Sprite portalAzulSprite(193, 193, 0, 0, 1, portalAzulTexture);

    //Portal naranja
    std::string portalNaranjaPath = "assets/portNaranja.png";
    SdlTexture portalNaranjaTexture(portalNaranjaPath, ventana);
    Sprite portalNaranjaSprite(193, 193, 0, 0, 1, portalNaranjaTexture);

    // Piedra
    Sprite piedra_sprite1(85, 83, 1, 4513, 1, efectos_textura);
    Sprite piedra_sprite2(85, 83, 87, 4513, 1, efectos_textura);
    Sprite piedra_sprite3(85, 83, 173, 4513, 1, efectos_textura);
    Sprite piedra_sprite4(85, 83, 259, 4513, 1, efectos_textura);
    Sprite piedra_sprite5(85, 83, 345, 4513, 1, efectos_textura);
    Sprite piedra_sprite6(85, 83, 431, 4513, 1, efectos_textura);
    Sprite piedra_sprite7(85, 83, 517, 4513, 1, efectos_textura);
    Sprite piedra_sprite8(85, 83, 603, 4513, 1, efectos_textura);

    // Bola de energia.
    Sprite bola_energia_sprite(171, 119, 1, 2000, 5, efectos_textura);

    // EmisorArriba
    Sprite emisor_arriba_sprite(193, 193, 1, 1242, 1, blocksTexture);
    // EmisorDerecha
    Sprite emisor_derecha_sprite(193, 193, 1, 1028, 1, blocksTexture);
    // EmisorAbajo
    Sprite emisor_abajo_sprite(193, 193, 1, 1456, 1, blocksTexture);
    // EmisorIzquierda
    Sprite emisor_izquierda_sprite(193, 193, 1, 814, 1, blocksTexture);

    // Receptores

    // ReceptorArriba
    // 	Activado
    Sprite receptor_arriba_activado_sprite(192, 192, 466, 1243, 1, blocksTexture);
    // Desactivado
    Sprite receptor_arriba_desactivado_sprite(192, 192, 233, 1243, 1, blocksTexture);

    // ReceptorDerecha
    // 	Activado
    Sprite receptor_derecha_activado_sprite(192, 192, 465, 1029, 1, blocksTexture);
    // Desactivado
    Sprite receptor_derecha_desactivado_sprite(192, 192, 235, 1029, 1, blocksTexture);

    // ReceptorIzquierda
    // 	Activado
    Sprite receptor_izquierda_activado_sprite(192, 192, 464, 814, 1, blocksTexture);
    // Desactivado
    Sprite receptor_izquierda_desactivado_sprite(192, 192, 235, 814, 1, blocksTexture);

    // ReceptorAbajo
    // 	Activado
    Sprite receptor_abajo_activado_sprite(192, 192, 468, 1457, 1, blocksTexture);
    // Desactivado
    Sprite receptor_abajo_desactivado_sprite(192, 192, 232, 1457, 1, blocksTexture);

    // Acido
    Sprite acido_sprite(300, 61, 1, 1545, 8, miscTexture);

    // Barra Energia
    Sprite barra_energia_sprite(8, 220, 528, 689, 1, miscTexture);

    ViewChell viewChell(ventana);

    renderizales[ID_CHELL] = &viewChell;
    renderizales[ID_BLOQUE_ROCA] = &bloqueSprite;
    renderizales[ID_DISPARO] = &disparoSprite;
    renderizales[ID_BLOQUE_METAL] = &bloqueMetalSprite;
    renderizales[ID_BLOQUE_DIAGONAL_0] = &bloqueMetalDiagoSprite;
    renderizales[ID_BLOQUE_DIAGONAL_90] = &bloqueMetalDiago90Sprite;
    renderizales[ID_BLOQUE_DIAGONAL_180] = &bloqueMetalDiago180Sprite;
    renderizales[ID_BLOQUE_DIAGONAL_270] = &bloqueMetalDiago270Sprite;
    renderizales[ID_PORTAL_AZUL] = &portalAzulSprite;
    renderizales[ID_PORTAL_NARANJA] = &portalNaranjaSprite;
    renderizales[ID_BOTON_APAGADO] = &botonSprite;
    renderizales[ID_COMPUERTA_CERRADA] = &compuertaCerradaSprite;
    renderizales[ID_COMPUERTA_ABRIENDO] = &compuertaAbriendoSprite;
    renderizales[ID_COMPUERTA_ABIERTA] = &compuertaAbiertaSprite;
    renderizales[ID_ROCA] = &piedra_sprite1;
    renderizales[ID_BOTON_PRENDIDO] = &botonPrendidoSprite;
    renderizales[ID_EMISORARRIBA] = &emisor_arriba_sprite;
    renderizales[ID_EMISORDERECHA] = &emisor_derecha_sprite;
    renderizales[ID_EMISORABAJO] = &emisor_abajo_sprite;
    renderizales[ID_EMISORIZQUIERDA] = &emisor_izquierda_sprite;
    renderizales[ID_BOLAENERGIA] = &bola_energia_sprite;
    renderizales[ID_RECEPTORARRIBA_ACTIVADO] = &receptor_arriba_activado_sprite;
    renderizales[ID_RECEPTORARRIBA_DESACTIVADO] = &receptor_arriba_desactivado_sprite;
    renderizales[ID_RECEPTORDERECHA_ACTIVADO] = &receptor_derecha_activado_sprite;
    renderizales[ID_RECEPTORDERECHA_DESACTIVADO] = &receptor_derecha_desactivado_sprite;
    renderizales[ID_RECEPTORABAJO_ACTIVADO] = &receptor_abajo_activado_sprite;
    renderizales[ID_RECEPTORABAJO_DESACTIVADO] = &receptor_abajo_desactivado_sprite;
    renderizales[ID_RECEPTORIZQUIERDA_ACTIVADO] = &receptor_izquierda_activado_sprite;
    renderizales[ID_RECEPTORIZQUIERDA_DESACTIVADO] = &receptor_izquierda_desactivado_sprite;
    renderizales[ID_ACIDO] = &acido_sprite;
    renderizales[ID_BARRAENERGIA] = &barra_energia_sprite;
}

Renderable * Renderizables::obtenerRenderizable(uint8_t id) {
    return renderizales[id];
}
