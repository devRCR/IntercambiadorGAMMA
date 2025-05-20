#include <Arduino.h>
#include "GUI_Interface.h"
#include "WheelComm.h"
#include "GripperComm.h"
#include "Protocol_Definitions.h"
#include "Buttons.h"

void setup() {
    // Inicializa el puerto USB para comunicación con GUI
    initGUI();
    while (SerialGUI.available()) SerialGUI.read();  // Limpia Serial (USB)

    // Inicializa UARTs con nodos esclavos
    initWheelComm();
    while (SerialWheel.available()) SerialWheel.read();  // Limpia Serial2 (Wheel)

    initGripperComm();
    while (SerialGripper.available()) SerialGripper.read();  // Limpia Serial1 (Gripper)

    // Pequeña espera para estabilización
    delay(200);

    // Configura los pines de botones como entradas pull-up
    initButtons();
}

void loop() {
    if (checkCommandFromGUI()) {
        handleGUICommand();
    }

    checkAckFromWheel();
    checkAckFromGripper();
}
