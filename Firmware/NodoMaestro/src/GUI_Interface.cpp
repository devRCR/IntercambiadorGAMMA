#include <Arduino.h>
#include "GUI_Interface.h"
#include "Protocol_Definitions.h"
#include "WheelComm.h"

static String guiInput = "";
static char guiCommand = 0;
static int guiValue = 0;

void initGUI() {
    SerialGUI.begin(115200);
    SerialGUI.println("Interfaz GUI lista.");
}

bool checkCommandFromGUI() {
    while (SerialGUI.available() > 0) {
        char c = SerialGUI.read();
        if (c == '\r') {
            if (guiInput.length() > 0) {
                guiCommand = guiInput.charAt(0);
                guiValue = guiInput.substring(1).toInt();
                guiInput = "";
                return true;
            }
        } else if (c != '\n') {
            guiInput += c;
        }
    }
    return false;
}

void handleGUICommand() {
    SerialGUI.print("Recibido: ");
    SerialGUI.print(guiCommand);
    SerialGUI.println(guiValue);

    if (
        (guiCommand == CMD_SHIELD && (guiValue == VAL_SHIELD_OPEN || guiValue == VAL_SHIELD_CLOSE)) ||
        (guiCommand == CMD_PLATE  && (guiValue == VAL_PLATE_UP     || guiValue == VAL_PLATE_DOWN)) ||
        (guiCommand == CMD_SAMPLE && (guiValue == VAL_SAMPLE_CYCLE || guiValue == VAL_SAMPLE_NEXT))
    ) {
        sendToWheel(guiCommand, guiValue);
        SerialGUI.println("→ Comando reenviado al Nodo Wheel");
    } else {
        SerialGUI.println("ERROR: Comando no reconocido o valor inválido.");
    }
}
