#include <Arduino.h>
#include "GUI_Interface.h"
#include "WheelComm.h"
#include "GripperComm.h"
#include "Protocol_Definitions.h"

void setup() {
    initGUI();
    while (SerialGUI.available()) SerialGUI.read();  // Flush Serial USB
    delay(200);  // UART stabilization

    initWheelComm();
    initGripperComm();

    // Comando inicial a Wheel (ej. detener todo)
    sendToWheel('T', 0);      // T0
    delay(50);
    sendToGripper('T', 0);    // T0
}

void loop() {
    if (checkCommandFromGUI()) {
        handleGUICommand();
    }

    checkAckFromWheel();
    checkAckFromGripper();
}
