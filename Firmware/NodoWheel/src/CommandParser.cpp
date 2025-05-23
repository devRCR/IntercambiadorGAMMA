#include <Arduino.h>
#include "CommandParser.h"
#include "Hardware_NodeWheel.h"

// Variables internas de comando
static String inputLocal = "";
static String inputMaster = "";
static char parsedCommand = 0;
static int parsedValue = -1;
static CommandSource parsedSource = SOURCE_NONE;

// Verifica si una cadena es numérica
bool isNumeric(const String& s) {
    if (s.length() == 0) return false;
    for (char c : s) {
        if (!isDigit(c)) return false;
    }
    return true;
}

// Comando desde Serial0 (USB/terminal)
bool checkLineFromLocal() {
    while (Serial.available() > 0) {
        char c = Serial.read();
        if (c == '\r') {
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
                inputLocal = "";
            }
        } else if (c != '\n') {
            inputLocal += c;
        }
    }
    return false;
}

// Comando desde Serial2 (Nodo Maestro)
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
                inputMaster = "";
            }
        } else if (c != '\n') {
            inputMaster += c;
        }
    }
    return false;
}

// Comando desde botón físico
void setCommandFromButton(char cmd, int val) {
    parsedCommand = cmd;
    parsedValue = val;
    parsedSource = SOURCE_BUTTON;
}

// Getters
char getParsedCommand() {
    return parsedCommand;
}

int getParsedValue() {
    return parsedValue;
}

CommandSource getParsedSource() {
    return parsedSource;
}

void clearParsedCommand() {
    parsedCommand = 0;
    parsedValue = -1;
    parsedSource = SOURCE_NONE;
}
// Función para imprimir el comando analizado (para depuración)