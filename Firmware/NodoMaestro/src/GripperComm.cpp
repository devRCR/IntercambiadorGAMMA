#include <Arduino.h>
#include "GripperComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String gripperInput = "";
static char ackType = 0;
static int ackValue = 0;

void initGripperComm() {
    SerialGripper.begin(9600);
    while (SerialGripper.available()) SerialGripper.read();  // Clear buffer
    SerialGUI.println("Communication with GripperNode initiated.");
}

void sendToGripper(char cmd, int val) {
    SerialGripper.print(cmd);
    SerialGripper.print(val);
    SerialGripper.print('\r');
}

void checkAckFromGripper() {
    while (SerialGripper.available() > 0) {
        char c = SerialGripper.read();
        if (c == '\r') {
            if (gripperInput.length() > 0) {
                ackType = gripperInput.charAt(0);
                ackValue = gripperInput.substring(1).toInt();
                gripperInput = "";

                if (ackType == 'K') {
                    SerialGUI.print("OK [Gripper]: ");
                    switch (ackValue) {
                        case STATE_GRIPPER_RELEASE: SerialGUI.println("Gripper released."); break;
                        case STATE_GRIPPER_CATCH: SerialGUI.println("Gripper caught."); break;
                        case STATE_POS_Y1: SerialGUI.println("Position Y1 reached."); break;
                        case STATE_POS_Y2: SerialGUI.println("Position Y2 reached."); break;
                        case STATE_POS_Y3: SerialGUI.println("Position Y3 reached."); break;
                        case STATE_EMERGENCY_STOP: SerialGUI.println("Emergency stop executed."); break;
                        default:
                            SerialGUI.print("State received = ");
                            SerialGUI.println(ackValue);
                    }
                } else if (ackType == 'E') {
                    SerialGUI.print("ERROR [GripperNode]: Code = ");
                    SerialGUI.println(ackValue);
                }
            }
        } else if (c != '\n') {
            gripperInput += c;
        }
    }
}
