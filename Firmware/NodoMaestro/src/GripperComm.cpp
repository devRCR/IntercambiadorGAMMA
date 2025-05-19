#include <Arduino.h>
#include "GripperComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String gripperInput = "";
static char ackType = 0;
static int ackValue = 0;

void initGripperComm() {
    SerialGripper.begin(9600);
    SerialGUI.println("Comunicación con GripperNode iniciada.");
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
                    SerialGUI.println(ackValue);
                } else if (ackType == 'E') {
                    SerialGUI.print("ERROR [Gripper]: Código = ");
                    SerialGUI.println(ackValue);
                }
            }
        } else if (c != '\n') {
            gripperInput += c;
        }
    }
}
