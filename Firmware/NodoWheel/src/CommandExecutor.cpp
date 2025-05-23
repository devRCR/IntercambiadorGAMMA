#include <Arduino.h>
#include "CommandExecutor.h"
#include "Hardware_NodeWheel.h"
#include "CommandDefinitions.h"
#include "Protocol_States.h"

#include "PlateControl.h"
#include "ShieldControl.h"
#include "SampleControl.h"

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
// Procesa el comando recibido desde cualquier fuente
// --------------------------------------------------
void executeCommand(char cmd, int val) {
    // Validación básica
    if (cmd == 0 || val < 0) {
        Serial.println("ERROR: Invalid command or non-numeric value.");
        sendERR(STATE_UNKNOWN);
        return;
    }

    Serial.print("Received : ");
    Serial.print(cmd);
    Serial.println(val);

    switch (cmd) {
        case CMD_SHIELD:
            if (val == VAL_SHIELD_OPEN || val == VAL_SHIELD_CLOSE) {
                processShieldCommand(val, true);  // true = responder al maestro
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_PLATE:
            if (val == VAL_PLATE_UP || val == VAL_PLATE_DOWN) {
                processPlateCommand(val, true);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_SAMPLE:
            if (val == VAL_SAMPLE_PREV || val == VAL_SAMPLE_NEXT) {
                processSampleCommand(val, true);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_STOP:
            if (val == VAL_STOP) {
                Serial.println(">> Emergency stop received.");
                sendACK(STATE_EMERGENCY_STOP);  // Respuesta inmediata permitida
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        default:
            sendERR(STATE_UNKNOWN);
    }
}
