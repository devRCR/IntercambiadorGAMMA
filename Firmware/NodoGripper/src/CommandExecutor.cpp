#include <Arduino.h>
#include "CommandExecutor.h"
#include "Hardware_GripperNode.h"
#include "CommandDefinitions.h"
#include "Protocol_States.h"

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
        Serial.println("ERROR: Comando inválido o valor no numérico.");
        sendERR(STATE_UNKNOWN);
        return;
    }

    Serial.print("Recibido → ");
    Serial.print(cmd);
    Serial.println(val);

    switch (cmd) {
        case CMD_GRIPPER:
            if (val == VAL_RELEASE) {
                Serial.println(">> Liberar Marinelli");
                sendACK(STATE_GRIPPER_RELEASE);
            } else if (val == VAL_CATCH) {
                Serial.println(">> Capturar Marinelli");
                sendACK(STATE_GRIPPER_CATCH);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_POSITION:
            if (val == VAL_POS_Y1) {
                Serial.println(">> Posición vertical Y1");
                sendACK(STATE_POS_Y1);
            } else if (val == VAL_POS_Y2) {
                Serial.println(">> Posición vertical Y2");
                sendACK(STATE_POS_Y2);
            } else if (val == VAL_POS_Y3) {
                Serial.println(">> Posición vertical Y3");
                sendACK(STATE_POS_Y3);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        case CMD_STOP:
            if (val == VAL_STOP) {
                Serial.println(">> Parada de emergencia");
                sendACK(STATE_EMERGENCY_STOP);
            } else {
                sendERR(STATE_UNKNOWN);
            }
            break;

        default:
            sendERR(STATE_UNKNOWN);
    }
}
