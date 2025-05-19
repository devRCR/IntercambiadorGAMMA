#include <Arduino.h>
#include "Hardware_NodeWheel.h"

// Variables internas
static String input = "";
static char parsedCommand = 0;
static int parsedValue = -1;

// Verifica si una cadena es numérica
bool isNumeric(const String& s) {
    if (s.length() == 0) return false;
    for (char c : s) {
        if (!isDigit(c)) return false;
    }
    return true;
}

// Procesa entrada por Serial2 desde el Nodo Maestro
bool checkLineFromMaster() {
    while (SerialNodeMaster.available() > 0) {
        char c = SerialNodeMaster.read();
        if (c == '\r') {
            if (input.length() > 1) {
                String rawValue = input.substring(1);
                if (isNumeric(rawValue)) {
                    parsedCommand = input.charAt(0);
                    parsedValue = rawValue.toInt();
                } else {
                    parsedCommand = 0;      // Marca como inválido
                    parsedValue = -1;
                }
                input = "";
                return true;
            } else {
                input = "";
            }
        } else if (c != '\n') {
            input += c;
        }
    }
    return false;
}

char getParsedCommand() {
    return parsedCommand;
}

int getParsedValue() {
    return parsedValue;
}
