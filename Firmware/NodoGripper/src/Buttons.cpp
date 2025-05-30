#include <Arduino.h>
#include "Buttons.h"
#include "Hardware_GripperNode.h"
#include "Protocol_Definitions.h"
#include "ZAxisControl.h"
#include "GripperControl.h"
#include "LCD_Display.h"

// =====================================================
// Tabla de botones físicos y sus comandos asociados
// =====================================================
ButtonAction buttons[] = {
    { PIN_BTN_GO_POS1,    CMD_ZAXIS,  ARG_ZAXIS_POS1 },
    { PIN_BTN_GO_POS2,    CMD_ZAXIS,  ARG_ZAXIS_POS2 },
    { PIN_BTN_GO_POS3,    CMD_ZAXIS,  ARG_ZAXIS_POS3 },

    { PIN_BTN_GRIPPER_CATCH_TOP,    CMD_GRIPPER, ARG_GRIPPER_CLOSE },
    { PIN_BTN_GRIPPER_RELEASE_TOP,  CMD_GRIPPER, ARG_GRIPPER_OPEN  },
    { PIN_BTN_GRIPPER_CATCH_BOTTOM, CMD_GRIPPER, ARG_GRIPPER_CLOSE },
    { PIN_BTN_GRIPPER_RELEASE_BOTTOM, CMD_GRIPPER, ARG_GRIPPER_OPEN },

    { PIN_BTN_STOP, CMD_ABORT, ARG_ABORT }
};

const int NUM_BUTTONS = sizeof(buttons) / sizeof(ButtonAction);

// Estado anterior y debounce
bool prevState[NUM_BUTTONS] = {true};
unsigned long lastPressTime[NUM_BUTTONS] = {0};
const unsigned long debounceDelay = 80;  // Tiempo mínimo entre activaciones

// =====================================================
// Configura los pines como entradas pull-up
// =====================================================
void initButtons() {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        pinMode(buttons[i].pin, INPUT_PULLUP);
    }
}

// =====================================================
// Escanea botones y ejecuta acciones locales
// =====================================================
void checkButtons() {
    for (int i = 0; i < NUM_BUTTONS; ++i) {
        bool current = digitalRead(buttons[i].pin);
        unsigned long now = millis();

        if (!current && prevState[i] && (now - lastPressTime[i] > debounceDelay)) {
            lastPressTime[i] = now;

            switch (buttons[i].command) {
                case CMD_ZAXIS:
                    moveZAxisToPosition(buttons[i].value);
                    break;

                case CMD_GRIPPER:
                    if (buttons[i].value == ARG_GRIPPER_OPEN) {
                        openGripper();
                    } else if (buttons[i].value == ARG_GRIPPER_CLOSE) {
                        closeGripper();
                    }
                    break;

                case CMD_ABORT:
                    openGripper();  // Acción de emergencia: abrir garra
                    disableZAxisMotor();  // Desactivar motor del eje Z
                    beepError();
                    break;
            }
        }

        prevState[i] = current;
    }
}