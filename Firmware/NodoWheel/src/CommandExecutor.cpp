#include <Arduino.h>
#include "CommandExecutor.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_Definitions.h"
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
    Serial.print("Received : ");
    Serial.print(cmd);
    Serial.println(val);

    switch (cmd) {
        // ===================== NODO WHEEL =====================
        case CMD_SHIELD:
            if (val == ARG_SHIELD_OPEN || val == ARG_SHIELD_CLOSE) {
                processShieldCommand(val, true);  // true = responde al maestro
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_PLATE:
            if (val == ARG_PLATE_UP || val == ARG_PLATE_DOWN) {
                processPlateCommand(val, true);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_SAMPLE_WHEEL:
            if (val == ARG_SAMPLE_NEXT) {
                processSampleCommand(val, true);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        // ===================== CONTROL GENERAL =====================
        case CMD_ABORT:
            Serial.println(">> Emergency stop received.");
            sendACK(STATE_EMERGENCY_STOP);  // Respuesta inmediata permitida
            break;

        case CMD_PING:
            Serial.println(">> Ping received.");
            sendACK(STATE_READY);  // Podrías usar otro estado según tu lógica
            break;

        default:
            sendERR(STATE_UNKNOWN);
            break;
    }
}
