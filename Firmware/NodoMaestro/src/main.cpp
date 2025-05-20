#include <Arduino.h>
#include "Protocol_Definitions.h"
#include "Hardware_NodeMaster.h"
#include "GUI_Interface.h"
#include "WheelComm.h"
#include "GripperComm.h"
#include "Buttons.h"

void setup() {
    // Inicializa el canal Serial USB para la GUI
    initGUI();
    while (SerialGUI.available()) SerialGUI.read();  // Limpia residuos

    delay(200);  // Estabiliza UARTs antes de usar

    // Inicializa UARTs con los nodos esclavos
    initWheelComm();    // Incluye verificación de respuesta
    initGripperComm();  // Incluye verificación de respuesta

    // Configura pines de botones como INPUT_PULLUP
    initButtons();
}

void loop() {
    // Comandos enviados desde la GUI (modo prueba / mantenimiento)
    if (checkCommandFromGUI()) {
        handleGUICommand();
    }

    // Comandos enviados desde los botones físicos (modo operativo principal)
    checkButtonsAndSendCommands();

    // Verifica respuestas de los nodos esclavos
    checkAckFromWheel();
    checkAckFromGripper();
}
