#include <Arduino.h>
#include "WheelComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String wheelInput = "";
static char ackType = 0;
static int ackValue = 0;
bool wheelNodeActive = false;

void initWheelComm() {
    SerialWheel.begin(9600);
    while (SerialWheel.available()) SerialWheel.read(); // Limpia buffer de entrada

    // Enviar comando de verificación (T0) al iniciar
    sendToWheel(CMD_STOP, VAL_STOP);
    unsigned long t_start = millis();
    wheelNodeActive = false;

    // Esperar respuesta por hasta 300 ms
while (millis() - t_start < 300) {
    if (SerialWheel.available()) {
        if (checkAckFromWheel()) {
            wheelNodeActive = true;
            break;
        }
    }
}

    // Mensaje de estado
    if (wheelNodeActive) {
        SerialGUI.println("WheelNode communication verified.");
    } else {
        SerialGUI.println("WARNING: No response from WheelNode.");
    }
}

void sendToWheel(char cmd, int val) {
    SerialWheel.print(cmd);
    SerialWheel.print(val);
    SerialWheel.print('\r');
}

bool checkAckFromWheel() {
    while (SerialWheel.available() > 0) {
        char c = SerialWheel.read();
        if (c == '\r') {
            if (wheelInput.length() > 0) {
                ackType = wheelInput.charAt(0);
                ackValue = wheelInput.substring(1).toInt();
                wheelInput = "";

                if (ackType == 'K') {
                    SerialGUI.print("OK [Wheel]: ");
                    switch (ackValue) {
                        case STATE_SHIELD_CLOSE: SerialGUI.println("Shield closed."); break;
                        case STATE_SHIELD_OPEN:  SerialGUI.println("Shield open."); break;
                        case STATE_PLATE_UP:     SerialGUI.println("Plate up."); break;
                        case STATE_PLATE_DOWN:   SerialGUI.println("Plate down."); break;
                        case STATE_SAMPLE_NEXT:  SerialGUI.println("Sample advanced."); break;
                        case STATE_SAMPLE_PREV:  SerialGUI.println("Sample reset."); break;
                        case STATE_EMERGENCY_STOP: SerialGUI.println("Emergency stop acknowledged."); break;
                        default:
                            SerialGUI.print("ACK code = ");
                            SerialGUI.println(ackValue);
                    }
                    return true;
                } else if (ackType == 'E') {
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

// Fin del archivo WheelComm.cpp