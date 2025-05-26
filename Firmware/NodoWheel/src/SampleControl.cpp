#include <Arduino.h>
#include "SampleControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"

// -------------------------------
// Variables internas de control
// -------------------------------

static bool advancing = false;
static unsigned long advanceStartTime = 0;
static const unsigned long ADVANCE_TIMEOUT_MS = 10000;
static int advanceMode = -1;  // 0: ciclo base (S0), 1: siguiente muestra (S1)
static bool replyToMaster = false;

// -----------------------------------------------------------
// Inicia el avance de muestra
// value = 0 (ciclo), 1 (siguiente)
// replyToMaster = true → se responderá con ACK/ERROR al maestro
// -----------------------------------------------------------
void processSampleCommand(int value, bool reply) {
    if (advancing) {
        Serial.println("Sample movement already in progress.");
        return;
    }

    if (value != 0 && value != 1) {
        Serial.println("Invalid sample command value.");
        return;
    }

    replyToMaster = reply;
    advanceMode = value;
    advanceStartTime = millis();
    advancing = true;

    Serial.println("Starting sample advance...");
    digitalWrite(RLY_SAMPLE_NEXT, HIGH);
}

// -----------------------------------------------------------
// Máquina de estados del avance de muestra
// Se llama continuamente desde loop()
// -----------------------------------------------------------
void updateSampleAdvance() {
    if (!advancing) return;

    // Confirmación de avance completado
    if (digitalRead(SENS_ORANGE)) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;

        if (advanceMode == 0) {
            Serial.println("Sample cycle complete.");
            if (replyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SAMPLE_CYCLE);
                SerialNodeMaster.print('\r');
                Serial.println(">> ACK sent: STATE_SAMPLE_CYCLE");
            }
        } else if (advanceMode == 1) {
            Serial.println("Next sample position reached.");
            if (replyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SAMPLE_NEXT);
                SerialNodeMaster.print('\r');
                Serial.println(">> ACK sent: STATE_SAMPLE_NEXT");
            }
        }
    }

    // Timeout
    if (millis() - advanceStartTime > ADVANCE_TIMEOUT_MS) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;
        Serial.println("Sample advance timeout.");

        if (replyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(4);  // Código de error de timeout
            SerialNodeMaster.print('\r');
            Serial.println(">> ERROR sent: timeout");
        }
    }
}
