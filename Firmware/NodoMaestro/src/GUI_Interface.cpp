#include <Arduino.h>
#include "GUI_Interface.h"
#include "Protocol_Definitions.h"
#include "WheelComm.h"
#include "GripperComm.h"

// ===========================================
// VARIABLES INTERNAS
// ===========================================
static String guiInput = "";
static char guiCommand = 0;
static int guiValue = -1;
static bool bootDiscard = true;


// ===========================================
// FUNCIONES AUXILIARES
// ===========================================

// Verifica si una cadena es completamente numérica
bool isNumeric(const String& s) {
    if (s.length() == 0) return false;
    for (char c : s) {
        if (!isDigit(c)) return false;
    }
    return true;
}

// ===========================================
// INICIALIZACIÓN DE PUERTO SERIAL
// ===========================================
void initGUI() {
    SerialGUI.begin(115200);
    while (SerialGUI.available()) SerialGUI.read();  // LIMPIA cualquier dato previo
    SerialGUI.println("GUI interface ready.");
}


// ===========================================
// RECEPCIÓN Y PARSEO DE COMANDOS DESDE GUI
// ===========================================

bool isValidCommandChar(char c) {
    return c == CMD_SHIELD || c == CMD_PLATE || c == CMD_SAMPLE ||
           c == CMD_GRIPPER || c == CMD_POSITION || c == CMD_STOP;
}

bool checkCommandFromGUI() {
    while (SerialGUI.available() > 0) {
        char c = SerialGUI.read();

        if (c == '\r') {
            if (guiInput.length() > 1 && isValidCommandChar(guiInput.charAt(0))) {
                String rawValue = guiInput.substring(1);
                if (isNumeric(rawValue)) {
                    guiCommand = guiInput.charAt(0);
                    guiValue = rawValue.toInt();
                    guiInput = "";
                    bootDiscard = false;  // Se procesó un comando válido
                    return true;
                }
            }

            guiInput = "";  // Limpia basura
        } else if (c != '\n') {
            guiInput += c;
        }
    }

    return false;
}

// ===========================================
// PROCESAMIENTO DEL COMANDO VALIDADO
// ===========================================
void handleGUICommand() {
    if (bootDiscard || guiCommand == 0 || guiValue < 0) {
        // No imprimir error durante fase de limpieza inicial
        return;
    }

    SerialGUI.print("Received: ");
    SerialGUI.print(guiCommand);
    SerialGUI.println(guiValue);

    // ---------------------------
    // Comandos para Nodo Wheel
    // ---------------------------
    if (
        (guiCommand == CMD_SHIELD && (guiValue == VAL_SHIELD_OPEN || guiValue == VAL_SHIELD_CLOSE)) ||
        (guiCommand == CMD_PLATE  && (guiValue == VAL_PLATE_UP    || guiValue == VAL_PLATE_DOWN)) ||
        (guiCommand == CMD_SAMPLE && (guiValue == VAL_SAMPLE_CYCLE || guiValue == VAL_SAMPLE_NEXT))
    ) {
        sendToWheel(guiCommand, guiValue);
        SerialGUI.println(">> Command forwarded to Wheel Node");
    }

    // ---------------------------
    // Comandos para Nodo Gripper
    // ---------------------------
    else if (
        (guiCommand == CMD_GRIPPER  && (guiValue == VAL_GRIPPER_RELEASE || guiValue == VAL_GRIPPER_CATCH)) ||
        (guiCommand == CMD_POSITION && (guiValue == VAL_POS_Y1 || guiValue == VAL_POS_Y2 || guiValue == VAL_POS_Y3)) ||
        (guiCommand == CMD_STOP     && guiValue == VAL_STOP)
    ) {
        sendToGripper(guiCommand, guiValue);
        SerialGUI.println(">> Command forwarded to Gripper Node");
    }

    // ---------------------------
    // Comando inválido
    // ---------------------------
    else {
        SerialGUI.println("ERROR: Unrecognized command or invalid value.");
    }
}
