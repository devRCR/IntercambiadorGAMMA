#include <Arduino.h>
#include "GUI_Interface.h"
#include "WheelComm.h"

void setup() {
    initGUI();
    initWheelComm();
}

void loop() {
    if (checkCommandFromGUI()) {
        handleGUICommand();
    }

    checkAckFromWheel();
}
