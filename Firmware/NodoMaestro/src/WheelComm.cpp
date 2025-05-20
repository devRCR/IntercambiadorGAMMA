#include <Arduino.h>
#include "WheelComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String wheelInput = "";
static char ackType = 0;
static int ackValue = 0;

void initWheelComm() {
    SerialWheel.begin(9600);
    while (SerialWheel.available()) SerialWheel.read();  // Clear buffer
    SerialGUI.println("Communication with WheelNode initiated.");
}

void sendToWheel(char cmd, int val) {
    SerialWheel.print(cmd);
    SerialWheel.print(val);
    SerialWheel.print('\r');
}

void checkAckFromWheel() {
    while (SerialWheel.available() > 0) {
        char c = SerialWheel.read();
        if (c == '\r') {
            if (wheelInput.length() > 0) {
                ackType = wheelInput.charAt(0);
                ackValue = wheelInput.substring(1).toInt();
                wheelInput = "";

                if (ackType == 'K') {
                    switch (ackValue) {
                        case STATE_SHIELD_CLOSE: SerialGUI.println("OK: Shield closed."); break;
                        case STATE_SHIELD_OPEN:  SerialGUI.println("OK: Shield opened."); break;
                        case STATE_PLATE_UP:     SerialGUI.println("OK: Plate in upper position."); break;
                        case STATE_PLATE_DOWN:   SerialGUI.println("OK: Plate in lower position."); break;
                        case STATE_SAMPLE_NEXT:  SerialGUI.println("OK: Next sample positioned."); break;
                        case STATE_SAMPLE_CYCLE: SerialGUI.println("OK: Previous sample positioned."); break;
                        default:
                            SerialGUI.print("OK: State received = ");
                            SerialGUI.println(ackValue);
                    }
                } else if (ackType == 'E') {
                    SerialGUI.print("ERROR [WheelNode]: Code = ");
                    SerialGUI.println(ackValue);
                }
            }
        } else if (c != '\n') {
            wheelInput += c;
        }
    }
}
