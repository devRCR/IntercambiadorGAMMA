#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

// =====================================================
// Estructura para describir acciones de botones físicos
// =====================================================
struct ButtonAction {
    uint8_t pin;        // Número de pin físico
    char command;       // Código de comando (según protocolo)
    int value;          // Valor asociado al comando
    enum Destino {
        WHEEL,          // Nodo Wheel
        GRIPPER,        // Nodo Gripper
        NINGUNO         // Sin nodo asociado (por ejemplo, pruebas)
    } destino;
};

// =====================================================
// Macro auxiliar para simplificar la declaración
// =====================================================
#define DEFINE_BUTTON(PIN, CMD, VAL, DEST) {PIN, CMD, VAL, ButtonAction::DEST}

// =====================================================
// Declaración de funciones públicas
// =====================================================
void initButtons();                     // Inicializa pines de botones como INPUT_PULLUP
void checkButtonsAndSendCommands();     // Revisa estado de botones y envía comandos

#endif // BUTTONS_H
