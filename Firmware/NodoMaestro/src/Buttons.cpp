#include <Arduino.h>
#include "Buttons.h"
#include "Hardware_NodeMaster.h"
#include "Protocol_Definitions.h"
#include "WheelComm.h"
#include "GripperComm.h"

// ==============================================
// LISTA DE BOTONES USANDO LA MACRO
// ==============================================
ButtonAction buttons[] = {
    // Wheel
    DEFINE_BUTTON(PIN_BTN_SAMPLE_NEXT,     CMD_SAMPLE,  VAL_SAMPLE_NEXT,    WHEEL),
    DEFINE_BUTTON(PIN_BTN_SAMPLE_CYCLE,    CMD_SAMPLE,  VAL_SAMPLE_CYCLE,   WHEEL),
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

    // FSM automática (sin acción por ahora)
    DEFINE_BUTTON(PIN_BTN_SEQUENCE_START,  'X',          0,                  NINGUNO)
};

// ==============================================
// ESTADOS ANTERIORES
// ==============================================
bool prevState[sizeof(buttons)/sizeof(ButtonAction)] = {true};

void initButtons() {
    for (auto &btn : buttons) {
        pinMode(btn.pin, INPUT_PULLUP);
    }
}

void checkButtonsAndSendCommands() {
    for (size_t i = 0; i < sizeof(buttons)/sizeof(ButtonAction); i++) {
        bool current = digitalRead(buttons[i].pin);
        if (!current && prevState[i]) {
            switch (buttons[i].destino) {
                case ButtonAction::WHEEL:
                    sendToWheel(buttons[i].command, buttons[i].value);
                    break;
                case ButtonAction::GRIPPER:
                    sendToGripper(buttons[i].command, buttons[i].value);
                    break;
                case ButtonAction::NINGUNO:
                    SerialGUI.println(">> Secuencia automática: aún no implementada.");
                    break;
            }
        }
        prevState[i] = current;
    }
}
