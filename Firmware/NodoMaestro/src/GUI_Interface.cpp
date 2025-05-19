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
    SerialGUI.println("Interfaz GUI lista.");
}

// ===========================================
// RECEPCIÓN Y PARSEO DE COMANDOS DESDE GUI
// ===========================================
bool checkCommandFromGUI() {
    while (SerialGUI.available() > 0) {
        char c = SerialGUI.read();
        if (c == '\r') {
            if (guiInput.length() > 1) {
                String rawValue = guiInput.substring(1);
                if (isNumeric(rawValue)) {
                    guiCommand = guiInput.charAt(0);
                    guiValue = rawValue.toInt();
                } else {
                    guiCommand = 0;
                    guiValue = -1;
                }
                guiInput = "";
                return true;
            } else {
                guiInput = "";
            }
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
    if (guiCommand == 0 || guiValue < 0) {
        SerialGUI.println("ERROR: Comando no válido o valor no numérico.");
        return;
    }

    SerialGUI.print("Recibido: ");
    SerialGUI.print(guiCommand);
    SerialGUI.println(guiValue);

    // ---------------------------
    // Comandos para Nodo Wheel
    // ---------------------------
    if (
        (guiCommand == CMD_SHIELD && (guiValue == VAL_SHIELD_OPEN || guiValue == VAL_SHIELD_CLOSE)) ||
        (guiCommand == CMD_PLATE  && (guiValue == VAL_PLATE_UP     || guiValue == VAL_PLATE_DOWN)) ||
        (guiCommand == CMD_SAMPLE && (guiValue == VAL_SAMPLE_CYCLE || guiValue == VAL_SAMPLE_NEXT))
    ) {
        sendToWheel(guiCommand, guiValue);
        SerialGUI.println("→ Comando reenviado al Nodo Wheel");
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
        SerialGUI.println("→ Comando reenviado al Nodo Gripper");
    }

    // ---------------------------
    // Comando inválido
    // ---------------------------
    else {
        SerialGUI.println("ERROR: Comando no reconocido o valor inválido.");
    }
}
