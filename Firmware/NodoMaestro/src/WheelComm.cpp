#include <Arduino.h>
#include "WheelComm.h"
#include "Protocol_Definitions.h"
#include "Protocol_States.h"

static String wheelInput = "";
static char ackType = 0;
static int ackValue = 0;

void initWheelComm() {
    SerialWheel.begin(9600);
    while (SerialWheel.available()) SerialWheel.read();  // Limpia residuos
    SerialGUI.println("Comunicación con Nodo Wheel iniciada.");
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
                        case STATE_SHIELD_CLOSE: SerialGUI.println("OK: Blindaje cerrado."); break;
                        case STATE_SHIELD_OPEN:  SerialGUI.println("OK: Blindaje abierto."); break;
                        case STATE_PLATE_UP:     SerialGUI.println("OK: Mesa en posición superior."); break;
                        case STATE_PLATE_DOWN:   SerialGUI.println("OK: Mesa en posición inferior."); break;
                        case STATE_SAMPLE_NEXT:  SerialGUI.println("OK: Muestra siguiente posicionada."); break;
                        case STATE_SAMPLE_CYCLE: SerialGUI.println("OK: Muestra previa posicionada."); break;
                        default:
                            SerialGUI.print("OK: Estado recibido = ");
                            SerialGUI.println(ackValue);
                    }
                } else if (ackType == 'E') {
                    SerialGUI.print("ERROR: Nodo Wheel reportó falla, Código = ");
                    SerialGUI.println(ackValue);
                }
            }
        } else if (c != '\n') {
            wheelInput += c;
        }
    }
}
