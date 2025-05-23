#include <Arduino.h>
#include "Buttons.h"
#include "Hardware_NodeMaster.h"
#include "Protocol_Definitions.h"
#include "WheelComm.h"
#include "GripperComm.h"

// =====================================================
// Lista de botones físicos definidos mediante macro
// =====================================================
ButtonAction buttons[] = {
    // Wheel
    DEFINE_BUTTON(PIN_BTN_SAMPLE_NEXT,     CMD_SAMPLE,  VAL_SAMPLE_NEXT,    WHEEL),
    DEFINE_BUTTON(PIN_BTN_SAMPLE_PREV,    CMD_SAMPLE,  VAL_SAMPLE_PREV,    WHEEL),
    DEFINE_BUTTON(PIN_BTN_PLATE_DOWN,      CMD_PLATE,   VAL_PLATE_DOWN,     WHEEL),
    DEFINE_BUTTON(PIN_BTN_PLATE_UP,        CMD_PLATE,   VAL_PLATE_UP,       WHEEL),
    DEFINE_BUTTON(PIN_BTN_SHIELD_OPEN,     CMD_SHIELD,  VAL_SHIELD_OPEN,    WHEEL),
    DEFINE_BUTTON(PIN_BTN_SHIELD_CLOSE,    CMD_SHIELD,  VAL_SHIELD_CLOSE,   WHEEL),

    // Gripper
    DEFINE_BUTTON(PIN_BTN_GRIPPER_RELEASE, CMD_GRIPPER, VAL_GRIPPER_RELEASE, GRIPPER),
    DEFINE_BUTTON(PIN_BTN_GRIPPER_CATCH,   CMD_GRIPPER, VAL_GRIPPER_CATCH,   GRIPPER),
    DEFINE_BUTTON(PIN_BTN_GO_POS_1,        CMD_POSITION,VAL_POS_Y1,          GRIPPER),
    DEFINE_BUTTON(PIN_BTN_GO_POS_2,        CMD_POSITION,VAL_POS_Y2,          GRIPPER),
    DEFINE_BUTTON(PIN_BTN_GO_POS_3,        CMD_POSITION,VAL_POS_Y3,          GRIPPER),
    DEFINE_BUTTON(PIN_BTN_STOP,            CMD_STOP,    VAL_STOP,            GRIPPER),

    // Secuencia automática (aún no implementada)
    DEFINE_BUTTON(PIN_BTN_SEQUENCE_START,  'X',          0,                  NINGUNO)
};

// =====================================================
// Variables de estado para detección de flancos y debounce
// =====================================================
#define NUM_BUTTONS (sizeof(buttons)/sizeof(ButtonAction))
bool prevState[NUM_BUTTONS] = {true};
unsigned long lastPressTime[NUM_BUTTONS] = {0};
const unsigned long debounceDelay = 80;  // Tiempo mínimo entre pulsos (ms)

// =====================================================
// Inicializa todos los botones físicos como INPUT_PULLUP
// =====================================================
void initButtons() {
    for (auto &btn : buttons) {
        pinMode(btn.pin, INPUT_PULLUP);
    }
}

// =====================================================
// Revisa el estado de los botones y ejecuta comandos
// =====================================================
void checkButtonsAndSendCommands() {
    for (size_t i = 0; i < NUM_BUTTONS; i++) {
        bool current = digitalRead(buttons[i].pin);
        unsigned long now = millis();

        // Detecta flanco descendente + espera de debounce
        if (!current && prevState[i] && (now - lastPressTime[i] > debounceDelay)) {
            switch (buttons[i].destino) {
                case ButtonAction::WHEEL:
                    sendToWheel(buttons[i].command, buttons[i].value);
                    break;
                case ButtonAction::GRIPPER:
                    sendToGripper(buttons[i].command, buttons[i].value);
                    break;
                case ButtonAction::NINGUNO:
                    SerialGUI.println("Automatic sequence not implemented.");
                    break;
            }
            lastPressTime[i] = now;
        }
        prevState[i] = current;
    }
}
