#include <Arduino.h>
#include "SampleControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"
#include "CommandParser.h"

// Estados internos
static bool advancing = false;
static unsigned long advanceStartTime = 0;
static const unsigned long ADVANCE_TIMEOUT_MS = 5000;
static int advanceMode = -1;  // 0: ciclo, 1: siguiente

// ---------------------------------------------
// Inicia el proceso de avance de muestra
// ---------------------------------------------
void startSampleAdvance(int mode) {
    // Evitar avance si ya está en curso
    if (advancing) return;

    Serial.println("Starting sample advance...");
    digitalWrite(RLY_SAMPLE_NEXT, HIGH);
    advanceMode = mode;
    advancing = true;
    advanceStartTime = millis();
}

// ---------------------------------------------
// Verifica fin del avance de muestra
// ---------------------------------------------
void updateSampleAdvance() {
    if (!advancing) return;

    if (digitalRead(SENS_ORANGE)) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;

        Serial.println("Sample advance completed.");
        if (getParsedSource() == SOURCE_SERIAL_MASTER) {
            SerialNodeMaster.print('K');
            SerialNodeMaster.print(
                advanceMode == 0 ? STATE_SAMPLE_CYCLE : STATE_SAMPLE_NEXT
            );
            SerialNodeMaster.print('\r');
        }
    }

    if (millis() - advanceStartTime > ADVANCE_TIMEOUT_MS) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;
        Serial.println("Sample advance timeout.");
        if (getParsedSource() == SOURCE_SERIAL_MASTER) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(4);  // Código de timeout
            SerialNodeMaster.print('\r');
        }
    }
}
