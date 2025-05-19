#include <Arduino.h>
#include "GUI_Interface.h"
#include "WheelComm.h"
#include "GripperComm.h"

void setup() {
    initGUI();
    initWheelComm();
    initGripperComm();
}

void loop() {
    if (checkCommandFromGUI()) {
        handleGUICommand();
    }

    checkAckFromWheel();
    checkAckFromGripper();
}
