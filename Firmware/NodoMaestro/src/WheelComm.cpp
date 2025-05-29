#include <Arduino.h>
#include "WheelComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"
#include "Hardware_NodeMaster.h"

// Variables internas
static String wheelInput = "";
static char ackType = 0;
static int ackValue = 0;
bool wheelNodeActive = false;

void initWheelComm() {
    SerialNodeWheel.begin(9600);
    while (SerialNodeWheel.available()) SerialNodeWheel.read();  // Limpia buffer

    // Enviar comando de verificación (ping)
    sendToWheel(CMD_PING, 0);
    unsigned long t_start = millis();
    wheelNodeActive = false;

    // Espera por respuesta durante 300 ms
    while (millis() - t_start < 300) {
        if (SerialNodeWheel.available()) {
            if (checkAckFromWheel()) {
                wheelNodeActive = true;
                break;
            }
        }
    }

    // Reporte en GUI
    if (wheelNodeActive) {
        SerialGUI.println("WheelNode communication verified.");
    } else {
        SerialGUI.println("WARNING: No response from WheelNode.");
    }
}

void sendToWheel(char cmd, int val) {
    SerialNodeWheel.print(cmd);
    SerialNodeWheel.print(val);
    SerialNodeWheel.print(CMD_TERMINATOR);
}

bool checkAckFromWheel() {
    while (SerialNodeWheel.available() > 0) {
        char c = SerialNodeWheel.read();
        if (c == CMD_TERMINATOR) {
            if (wheelInput.length() > 0) {
                ackType = wheelInput.charAt(0);
                ackValue = wheelInput.substring(1).toInt();
                wheelInput = "";

                if (ackType == RESP_ACK) {
                    SerialGUI.print("OK [Wheel]: ");
                    switch (ackValue) {
                        case STATE_SHIELD_CLOSED: SerialGUI.println("Shield closed."); break;
                        case STATE_SHIELD_OPEN:   SerialGUI.println("Shield open."); break;
                        case STATE_PLATE_UP:      SerialGUI.println("Plate up."); break;
                        case STATE_PLATE_DOWN:    SerialGUI.println("Plate down."); break;
                        case STATE_SAMPLE_NEXT:   SerialGUI.println("Sample advanced."); break;
                        case STATE_SAMPLE_CYCLE:  SerialGUI.println("Sample reset."); break;
                        case STATE_EMERGENCY_STOP:SerialGUI.println("Emergency stop acknowledged."); break;
                        default:
                            SerialGUI.print("ACK code = ");
                            SerialGUI.println(ackValue);
                    }
                    return true;
                } else if (ackType == RESP_ERROR) {
                    SerialGUI.print("ERROR [Wheel]: Code = ");
                    SerialGUI.println(ackValue);
                    return false;
                }
            }
        } else if (c != '\n') {
            wheelInput += c;
        }
    }
    return false;
}
