#include <Arduino.h>
#include "CommandExecutor.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"
#include "CommandDefinitions.h"

void sendACK(int state) {
    SerialNodeMaster.print('K');
    SerialNodeMaster.print(state);
    SerialNodeMaster.print('\r');
}

void sendERR(int code) {
    SerialNodeMaster.print('E');
    SerialNodeMaster.print(code);
    SerialNodeMaster.print('\r');
}

void executeCommand(char cmd, int val) {
    if (cmd == 0 || val < 0) {
        Serial.println("ERROR: Comando no válido o valor no numérico.");
        sendERR(STATE_UNKNOWN);
        return;
    }
    Serial.print("Recibido → ");
    Serial.print(cmd);
    Serial.println(val);

    switch (cmd) {
        case CMD_SHIELD:
            if (val == VAL_SHIELD_OPEN) {
                Serial.println(">> Abrir blindaje");
                sendACK(STATE_SHIELD_OPEN);
            } else if (val == VAL_SHIELD_CLOSE) {
                Serial.println(">> Cerrar blindaje");
                sendACK(STATE_SHIELD_CLOSE);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_PLATE:
            if (val == VAL_PLATE_UP) {
                Serial.println(">> Subir mesa");
                sendACK(STATE_PLATE_UP);
            } else if (val == VAL_PLATE_DOWN) {
                Serial.println(">> Bajar mesa");
                sendACK(STATE_PLATE_DOWN);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_SAMPLE:
            if (val == VAL_SAMPLE_PREV) {
                Serial.println(">> Retroceder muestra");
                sendACK(STATE_SAMPLE_PREV);
            } else if (val == VAL_SAMPLE_NEXT) {
                Serial.println(">> Avanzar muestra");
                sendACK(STATE_SAMPLE_NEXT);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        default:
            sendERR(STATE_UNKNOWN);
    }
}
