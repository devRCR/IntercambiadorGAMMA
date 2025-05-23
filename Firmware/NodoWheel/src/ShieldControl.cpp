#include <Arduino.h>
#include "ShieldControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"
#include "CommandParser.h"

// Estados internos
#define SHIELD_OPEN   0
#define SHIELD_CLOSE  1

static uint8_t SHIELD_STATE = 0;  // 0: inactivo, 1: abriendo, 2: cerrando
static unsigned long shieldStartTime = 0;
static const unsigned long SHIELD_TIMEOUT_MS = 5000;

// -------------------------------------------------
// Inicia el proceso de apertura o cierre del blindaje
// -------------------------------------------------
void startShieldAction(int action) {
    // Validar que la mesa esté abajo
    if (!(digitalRead(SENSOR_BOTTOM1) && digitalRead(SENSOR_BOTTOM2))) {
        Serial.println("Shield blocked: plate not down.");
        if (getParsedSource() == SOURCE_SERIAL_MASTER) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(2); // Código: condición de seguridad violada
            SerialNodeMaster.print('\r');
        }
        return;
    }

    if (action == SHIELD_OPEN) {
        Serial.println("Opening shield...");
        digitalWrite(RLY_DOOR_OPEN, HIGH);
        SHIELD_STATE = 1;
    } else if (action == SHIELD_CLOSE) {
        Serial.println("Closing shield...");
        digitalWrite(RLY_DOOR_CLOSE, HIGH);
        SHIELD_STATE = 2;
    }

    shieldStartTime = millis();
}

// -------------------------------------------------
// Verifica si el blindaje alcanzó su posición
// -------------------------------------------------
void updateShieldAction() {
    if (SHIELD_STATE == 0) return;

    // ABRIENDO
    if (SHIELD_STATE == 1) {
        if (digitalRead(SENS_GREEN)) {
            digitalWrite(RLY_DOOR_OPEN, LOW);
            SHIELD_STATE = 0;
            Serial.println("Shield opened.");
            if (getParsedSource() == SOURCE_SERIAL_MASTER) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SHIELD_OPEN);
                SerialNodeMaster.print('\r');
            }
        }
    }

    // CERRANDO
    else if (SHIELD_STATE == 2) {
        if (digitalRead(SENS_BLUE)) {
            digitalWrite(RLY_DOOR_CLOSE, LOW);
            SHIELD_STATE = 0;
            Serial.println("Shield closed.");
            if (getParsedSource() == SOURCE_SERIAL_MASTER) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SHIELD_CLOSE);
                SerialNodeMaster.print('\r');
            }
        }
    }

    // TIMEOUT
    if (millis() - shieldStartTime > SHIELD_TIMEOUT_MS) {
        digitalWrite(RLY_DOOR_OPEN, LOW);
        digitalWrite(RLY_DOOR_CLOSE, LOW);
        SHIELD_STATE = 0;
        Serial.println("Shield action timeout.");
        if (getParsedSource() == SOURCE_SERIAL_MASTER) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(3);  // Código de timeout
            SerialNodeMaster.print('\r');
        }
    }
}
