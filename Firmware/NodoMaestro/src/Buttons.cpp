#include <Arduino.h>
#include "Hardware_NodeMaster.h"
#include "Buttons.h"

void initButtons() {
    // Rueda de muestras (Wheel)
    pinMode(PIN_BTN_SAMPLE_NEXT, INPUT_PULLUP);
    pinMode(PIN_BTN_SAMPLE_CYCLE, INPUT_PULLUP);

    // Mesa niveladora (Wheel)
    pinMode(PIN_BTN_PLATE_DOWN, INPUT_PULLUP);
    pinMode(PIN_BTN_PLATE_UP, INPUT_PULLUP);

    // Blindaje (Wheel)
    pinMode(PIN_BTN_SHIELD_OPEN, INPUT_PULLUP);
    pinMode(PIN_BTN_SHIELD_CLOSE, INPUT_PULLUP);

    // Parada de emergencia (Gripper)
    pinMode(PIN_BTN_STOP, INPUT_PULLUP);

    // Posiciones verticales (Gripper)
    pinMode(PIN_BTN_GO_POS_1, INPUT_PULLUP);
    pinMode(PIN_BTN_GO_POS_2, INPUT_PULLUP);
    pinMode(PIN_BTN_GO_POS_3, INPUT_PULLUP);

    // Captura y liberación (Gripper)
    pinMode(PIN_BTN_GRIPPER_CATCH, INPUT_PULLUP);
    pinMode(PIN_BTN_GRIPPER_RELEASE, INPUT_PULLUP);

    // Iniciar secuencia automática
    pinMode(PIN_BTN_SEQUENCE_START, INPUT_PULLUP);
}
