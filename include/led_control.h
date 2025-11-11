/*
    Led control
    encargado de manejar los stados de los leds
    dependiendo de las acciones del usuario
    y del estado del sistema.

    3 Leds. Pines: D6, D7, D8
    D6 - Led Rojo
    D7 - Led Verde
    D8 - Led Blanco.

    booting() - Secuencia de arranque de los leds
    parapadean los tres leds y el blanco queda fijo indicando
    que el sistema esta listo y escaniando.

    Detection() - secuencia de deteccion: Cuando el modulo PN532
    detecta una tarjeta, el led verde parpadea 3 veces.

    Denied() - secuencia de acceso denegado: El led rojo parpadea 3 veces.
    Granted() - secuencia de acceso concedido: El led verde queda fijo por 3 segundos.

    posible implementacion a futuro:
    Warning() - secuencia de advertencia: El led rojo y verde parpadean
    Reboot() - secuancia de reinio: los tres leds parpadean constantemente si el sistema
    pide reinicio (por ejemplo, si hay un error grave o se agrego un Tag en la memoria LittleFs).
*/

#pragma once
#include <Arduino.h>

#define LED_RED_PIN     6
#define LED_GREEN_PIN   7
#define LED_WHITE_PIN   8

void led_setup();
void led_booting();
void led_detection();
void led_denied();
void led_granted();