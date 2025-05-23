#include <Arduino.h>
#include "SampleControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"
#include "CommandParser.h"

static bool advancing = false;
static unsigned long advanceStartTime = 0;
static const unsigned long ADVANCE_TIMEOUT_MS = 5000;
static int advanceMode = -1;
static bool replyToMaster = false;

void processSampleCommand(int value, bool reply) {
    if (advancing) return;

    replyToMaster = reply;
    advanceMode = value;
    advanceStartTime = millis();
    advancing = true;

    Serial.println("Starting sample advance...");
    digitalWrite(RLY_SAMPLE_NEXT, HIGH);
}

void updateSampleAdvance() {
    if (!advancing) return;

    if (digitalRead(SENS_ORANGE)) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;
        Serial.println("Sample advance complete.");
        if (replyToMaster) {
            SerialNodeMaster.print('K');
            SerialNodeMaster.print(advanceMode == 0 ? STATE_SAMPLE_CYCLE : STATE_SAMPLE_NEXT);
            SerialNodeMaster.print('\r');
        }
    }

    if (millis() - advanceStartTime > ADVANCE_TIMEOUT_MS) {
        digitalWrite(RLY_SAMPLE_NEXT, LOW);
        advancing = false;
        Serial.println("Sample advance timeout.");
        if (replyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(4);
            SerialNodeMaster.print('\r');
        }
    }
}
