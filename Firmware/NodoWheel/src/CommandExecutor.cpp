#include <Arduino.h>
#include "CommandExecutor.h"
#include "Hardware_NodeWheel.h"
#include "CommandDefinitions.h"
#include "Protocol_States.h"

// --------------------------------------------------
// Envía ACK con código de estado exitoso
// --------------------------------------------------
void sendACK(int state) {
    SerialNodeMaster.print('K');
    SerialNodeMaster.print(state);
    SerialNodeMaster.print('\r');
}

// --------------------------------------------------
// Envía mensaje de error con código
// --------------------------------------------------
void sendERR(int code) {
    SerialNodeMaster.print('E');
    SerialNodeMaster.print(code);
    SerialNodeMaster.print('\r');
}

// --------------------------------------------------
// Procesa el comando recibido desde el maestro
// --------------------------------------------------
void executeCommand(char cmd, int val) {
    // Validación básica de datos
    if (cmd == 0 || val < 0) {
        Serial.println("ERROR: Invalid command or non-numeric value.");
        sendERR(STATE_UNKNOWN);
        return;
    }

    Serial.print("Received → ");
    Serial.print(cmd);
    Serial.println(val);

    switch (cmd) {

        // Comando de control de blindaje
        case CMD_SHIELD:
            if (val == VAL_SHIELD_OPEN) {
                Serial.println(">> Open shield");
                sendACK(STATE_SHIELD_OPEN);
            } else if (val == VAL_SHIELD_CLOSE) {
                Serial.println(">> Close shield");
                sendACK(STATE_SHIELD_CLOSE);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        // Comando de control de mesa niveladora
        case CMD_PLATE:
            if (val == VAL_PLATE_UP) {
                Serial.println(">> Raise plate");
                sendACK(STATE_PLATE_UP);
            } else if (val == VAL_PLATE_DOWN) {
                Serial.println(">> Lower plate");
                sendACK(STATE_PLATE_DOWN);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        // Comando de control de rueda de muestras
        case CMD_SAMPLE:
            if (val == VAL_SAMPLE_PREV) {
                Serial.println(">> Reset sample position");
                sendACK(STATE_SAMPLE_PREV);
            } else if (val == VAL_SAMPLE_NEXT) {
                Serial.println(">> Advance to next sample");
                sendACK(STATE_SAMPLE_NEXT);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        // Comando de parada de emergencia (sin acción física)
        case CMD_STOP:
            if (val == VAL_STOP) {
                Serial.println(">> Emergency stop received (no action)");
                sendACK(STATE_EMERGENCY_STOP);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        // Comando desconocido
        default:
            sendERR(STATE_UNKNOWN);
    }
}
