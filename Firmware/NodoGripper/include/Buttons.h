#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

// Estructura para asociar un botón con una acción
struct ButtonAction {
    uint8_t pin;     // Pin físico del botón
    char command;    // Comando asociado (e.g., CMD_ZAXIS, CMD_GRIPPER, CMD_ABORT)
    int value;       // Valor del comando (ARG_ZAXIS_POS1, ARG_GRIPPER_CLOSE, etc.)
};

// Inicialización y escaneo de botones
void initButtons();
void checkButtons();

#endif // BUTTONS_H
