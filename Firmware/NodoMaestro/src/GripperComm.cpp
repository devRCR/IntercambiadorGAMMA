#include <Arduino.h>
#include "GripperComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String gripperInput = "";
static char ackType = 0;
static int ackValue = 0;
bool gripperNodeActive = false;

bool checkAckFromGripper() {
    while (SerialGripper.available() > 0) {
        char c = SerialGripper.read();
        if (c == '\r') {
            if (gripperInput.length() > 0) {
                ackType = gripperInput.charAt(0);
                ackValue = gripperInput.substring(1).toInt();
                gripperInput = "";

                if (ackType == 'K') {
                    SerialGUI.print("OK [Gripper]: ");
                    // Interpretar ACK específico
                    switch (ackValue) {
                        case STATE_GRIPPER_RELEASE:
                            SerialGUI.println("Gripper released.");
                            break;
                        case STATE_GRIPPER_CATCH:
                            SerialGUI.println("Gripper captured.");
                            break;
                        case STATE_POS_Y1:
                            SerialGUI.println("Position Y1 reached.");
                            break;
                        case STATE_POS_Y2:
                            SerialGUI.println("Position Y2 reached.");
                            break;
                        case STATE_POS_Y3:
                            SerialGUI.println("Position Y3 reached.");
                            break;
                        case STATE_EMERGENCY_STOP:
                            SerialGUI.println("Emergency stop executed.");
                            break;
                        default:
                            SerialGUI.print("ACK code = ");
                            SerialGUI.println(ackValue);
                    }
                    return true;  // ACK válido
                } else if (ackType == 'E') {
                    SerialGUI.print("ERROR [Gripper]: Code = ");
                    SerialGUI.println(ackValue);
                    return false;
                }
            }
        } else if (c != '\n') {
            gripperInput += c;
        }
    }
    return false;
}

void initGripperComm() {
    SerialGripper.begin(9600);
    while (SerialGripper.available()) SerialGripper.read();

    sendToGripper(CMD_STOP, VAL_STOP);
    unsigned long t_start = millis();
    gripperNodeActive = false;

    while (millis() - t_start < 300) {
        if (SerialGripper.available()) {
            if (checkAckFromGripper()) {
                gripperNodeActive = true;
                break;
            }
        }
    }

    if (gripperNodeActive) {
        SerialGUI.println("GripperNode communication verified.");
    } else {
        SerialGUI.println("WARNING: No response from GripperNode.");
    }
}

void sendToGripper(char cmd, int val) {
    SerialGripper.print(cmd);
    SerialGripper.print(val);
    SerialGripper.print('\r');
}


// Fin del archivo GripperComm.cpp