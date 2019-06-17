
#ifndef CONTADOR_TIEMPO_H
#define CONTADOR_TIEMPO_H


class ContadorTiempo {
private:
    uint32_t ticks_comienzo;
    uint32_t ticks_pausado;
    bool pausado;
    bool comenzo;
public:
    ContadorTiempo();
    // Comienza a contar ticks.
    void comenzar();
    // Deja de contar ticks.
    void parar();
    // Pausa el conteo de ticks.
    void pausar();
    // Despausa el conteo de ticks.
    void despausar();
    // Devuelve los ticks contados hasta el momento (si se habia pausado, la
    // cantidad de ticks que se devuelve es la contada hasta ese momento).
    uint32_t obtenerTicks();
    ~ContadorTiempo() = default;
};


#endif //CONTADOR_TIEMPO_H
