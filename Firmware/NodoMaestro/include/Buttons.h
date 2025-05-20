#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

void initButtons();
void checkButtonsAndSendCommands();

// ==============================================
// MACRO PARA DECLARAR BOTONES CON ACCIÓN
// ==============================================
#define DEFINE_BUTTON(PIN, CMD, VAL, DEST) {PIN, CMD, VAL, ButtonAction::DEST}

// ==============================================
// ENUM DE DESTINO DEL COMANDO
// ==============================================
struct ButtonAction {
    uint8_t pin;
    char command;
    int value;
    enum Destino {WHEEL, GRIPPER, NINGUNO} destino;
};

#endif
