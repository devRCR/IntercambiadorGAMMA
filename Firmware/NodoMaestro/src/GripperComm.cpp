#include <Arduino.h>
#include "GripperComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"
#include "Hardware_NodeMaster.h"

static String gripperInput = "";
static char ackType = 0;
static int ackValue = 0;
bool gripperNodeActive = false;

bool checkAckFromGripper() {
    while (SerialNodeGripper.available() > 0) {
        char c = SerialNodeGripper.read();
        if (c == CMD_TERMINATOR) {
            if (gripperInput.length() > 0) {
                ackType = gripperInput.charAt(0);
                ackValue = gripperInput.substring(1).toInt();
                gripperInput = "";

                if (ackType == RESP_ACK) {
                    SerialGUI.print("OK [Gripper]: ");
                    switch (ackValue) {
                        case STATE_GRIPPER_OPEN:
                            SerialGUI.println("Gripper released.");
                            break;
                        case STATE_GRIPPER_CLOSED:
                            SerialGUI.println("Gripper captured.");
                            break;
                        case STATE_ZAXIS_POS1:
                            SerialGUI.println("Z-axis position 1 (bottom).");
                            break;
                        case STATE_ZAXIS_POS2:
                            SerialGUI.println("Z-axis position 2 (middle).");
                            break;
                        case STATE_ZAXIS_POS3:
                            SerialGUI.println("Z-axis position 3 (top).");
                            break;
                        case STATE_EMERGENCY_STOP:
                            SerialGUI.println("Emergency stop executed.");
                            break;
                        default:
                            SerialGUI.print("ACK code = ");
                            SerialGUI.println(ackValue);
                    }
                    return true;
                } else if (ackType == RESP_ERROR) {
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
    SerialNodeGripper.begin(9600);
    while (SerialNodeGripper.available()) SerialNodeGripper.read();

    sendToGripper(CMD_PING, 0);  // Verificación de nodo al inicio
    unsigned long t_start = millis();
    gripperNodeActive = false;

    while (millis() - t_start < 300) {
        if (SerialNodeGripper.available()) {
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
    SerialNodeGripper.print(cmd);
    SerialNodeGripper.print(val);
    SerialNodeGripper.print(CMD_TERMINATOR);
}
