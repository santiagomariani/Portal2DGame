
#ifndef CONFIG_H
#define CONFIG_H

#include <Box2D/Common/b2Settings.h>

struct Config{
    // Gravedad (eje y)
    float gravedad = -9.8;

    float escala_gravedad_chell = 1.0f;
    
    // Velocidad caminata de Chell
    float velocidad_chell = 4;

    float salto_chell = 6;

    // Ancho del Chell
    float tam_chell_x = 0.2f;

    // Alto de Chell
    float tam_chell_y = 0.39583f;

    // Alto y ancho del bloque
    float tam_bloque = 0.5f;

    // Ancho base del boton
    float tam_base_boton_x = 0.5;

    // Alto base del boton
    float tam_base_boton_y = 0.1;

    // Ancho sensor del boton (sensor del peso)
    float tam_sensor_boton_x = 0.25;

    // Alto sensor del boton (sensor del peso)
    float tam_sensor_boton_y = 0.025;

    // Radio del disparo de Chell
    float radio_disparo = 0.15f;

    // Velocidad del disparo
    float velocidad_disparo = 5;

    // Ancho portal
    float tam_portal_x = 0.04;

    // Alto portal
    float tam_portal_y = 0.45;

    // Ancho y alto de rocas
    float tam_roca = 0.15f;

    // Ancho del acido
    float tam_acido_x = 0.5;

    // Alto acido
    float tam_acido_y = 0.06;

    // Ancho compuerta
    float tam_compuerta_x = 0.5;

    // Alto compuerta
    float tam_compuerta_y = 0.94;
    
    // Ancho y alto de los receptores
    float  tam_receptor = 0.5f;

    // Alto barra energia
    float tam_barra_energia_y = 1;

    // Ancho barra energia
    float tam_barra_energia_x = 0.05;

    // Radio bola energia
    float radio_bola_energia = 0.40f;

    // Velocidad constante de la bola de energia
    float vel_bola_energia = 0.3;

    // Ancho y alto de los emisores de energia
    float tam_emisor = 0.5f;
};

extern Config config;

#endif
