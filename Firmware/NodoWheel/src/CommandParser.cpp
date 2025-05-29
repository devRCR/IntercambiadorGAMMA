#include <Arduino.h>
#include "CommandParser.h"
#include "Hardware_NodeWheel.h"  // Definición de SerialNodeMaster

// ============================================================================
// VARIABLES INTERNAS PARA RECEPCIÓN Y ALMACENAMIENTO DE COMANDOS
// ============================================================================

static String inputLocal = "";     // Buffer para entrada desde USB (Serial)
static String inputMaster = "";    // Buffer para entrada desde Nodo Maestro
static char parsedCommand = 0;     // Carácter del comando (ej. 'G', 'Z')
static int parsedValue = -1;       // Valor entero asociado al comando (ej. 0, 1)
static CommandSource parsedSource = SOURCE_NONE; // Origen del comando actual


// ============================================================================
// FUNCIÓN AUXILIAR: Verifica si una cadena es completamente numérica
// ============================================================================
bool isNumeric(const String& s) {
    if (s.length() == 0) return false;
    for (char c : s) {
        if (!isDigit(c)) return false;
    }
    return true;
}


// ============================================================================
// FUNCIÓN: checkLineFromLocal()
// Lee el puerto USB (Serial) y analiza si hay un comando válido disponible.
// ============================================================================
bool checkLineFromLocal() {
    while (Serial.available() > 0) {
        char c = Serial.read();

        if (c == '\r') {
            // Fin de línea: procesar si es válido
            if (inputLocal.length() > 1) {
                String val = inputLocal.substring(1);
                if (isNumeric(val)) {
                    parsedCommand = inputLocal.charAt(0);
                    parsedValue = val.toInt();
                    parsedSource = SOURCE_SERIAL_LOCAL;
                } else {
                    parsedCommand = 0;
                    parsedValue = -1;
                    parsedSource = SOURCE_SERIAL_LOCAL;
                }
                inputLocal = "";
                return true;
            } else {
                inputLocal = "";  // Comando vacío o inválido
            }
        } else if (c != '\n') {
            inputLocal += c;
        }
    }
    return false;
}


// ============================================================================
// FUNCIÓN: checkLineFromMaster()
// Lee el puerto SerialNodeMaster y analiza si hay un comando válido.
// ============================================================================
bool checkLineFromMaster() {
    while (SerialNodeMaster.available() > 0) {
        char c = SerialNodeMaster.read();

        if (c == '\r') {
            if (inputMaster.length() > 1) {
                String val = inputMaster.substring(1);
                if (isNumeric(val)) {
                    parsedCommand = inputMaster.charAt(0);
                    parsedValue = val.toInt();
                    parsedSource = SOURCE_SERIAL_MASTER;
                } else {
                    parsedCommand = 0;
                    parsedValue = -1;
                    parsedSource = SOURCE_SERIAL_MASTER;
                }
                inputMaster = "";
                return true;
            } else {
                inputMaster = "";  // Comando vacío o inválido
            }
        } else if (c != '\n') {
            inputMaster += c;
        }
    }
    return false;
}


// ============================================================================
// FUNCIÓN: setCommandFromButton()
// Permite registrar un comando proveniente de un botón físico externo.
// ============================================================================
void setCommandFromButton(char cmd, int val) {
    parsedCommand = cmd;
    parsedValue = val;
    parsedSource = SOURCE_BUTTON;
}


// ============================================================================
// FUNCIONES GETTER
// Proveen acceso al comando recibido y su fuente
// ============================================================================
char getParsedCommand() {
    return parsedCommand;
}

int getParsedValue() {
    return parsedValue;
}

CommandSource getParsedSource() {
    return parsedSource;
}


// ============================================================================
// FUNCIÓN: clearParsedCommand()
// Limpia las variables internas para aceptar un nuevo comando.
// ============================================================================
void clearParsedCommand() {
    parsedCommand = 0;
    parsedValue = -1;
    parsedSource = SOURCE_NONE;
}
