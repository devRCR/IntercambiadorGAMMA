#include <Arduino.h>
#include "ShieldControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"

// -------------------------------
// Variables internas de control
// -------------------------------

#define SHIELD_OPEN   0
#define SHIELD_CLOSE  1

static uint8_t SHIELD_STATE = 0;               // 0: inactivo, 1: abriendo, 2: cerrando
static unsigned long shieldStartTime = 0;
static const unsigned long SHIELD_TIMEOUT_MS = 25000;
static bool currentReplyToMaster = false;

// -----------------------------------------------------------
// Inicia el proceso de apertura o cierre del blindaje
// value = 0 (abrir), 1 (cerrar)
// replyToMaster = true → se responderá con ACK/ERROR al maestro
// -----------------------------------------------------------
void processShieldCommand(int value, bool replyToMaster) {
    currentReplyToMaster = replyToMaster;

    // Si el blindaje ya está en el estado solicitado, responder inmediatamente con ACK
    if (value == SHIELD_OPEN && digitalRead(SENS_GREEN)) {
        Serial.println("Shield already open.");
        if (currentReplyToMaster) {
            SerialNodeMaster.print('K');
            SerialNodeMaster.print(STATE_SHIELD_OPEN);
            SerialNodeMaster.print('\r');
        }
        return;
    }
    if (value == SHIELD_CLOSE && digitalRead(SENS_BLUE)) {
        Serial.println("Shield already closed.");
        if (currentReplyToMaster) {
            SerialNodeMaster.print('K');
            SerialNodeMaster.print(STATE_SHIELD_CLOSED);
            SerialNodeMaster.print('\r');
        }
        return;
    }

    // Condición de seguridad: la mesa debe estar abajo para operar el blindaje
    if (!(digitalRead(SENSOR_BOTTOM1) && digitalRead(SENSOR_BOTTOM2))) {
        Serial.println("Safety violation: plate is not down.");
        if (currentReplyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(2);  // Código de error: condición de seguridad
            SerialNodeMaster.print('\r');
        }
        return;
    }

    shieldStartTime = millis();

    if (value == SHIELD_OPEN) {
        Serial.println("Opening shield...");
        digitalWrite(RLY_DOOR_OPEN, HIGH);
        SHIELD_STATE = 1;
    } else if (value == SHIELD_CLOSE) {
        Serial.println("Closing shield...");
        digitalWrite(RLY_DOOR_CLOSE, HIGH);
        SHIELD_STATE = 2;
    } else {
        Serial.println("Invalid shield command value.");
    }
}

// -----------------------------------------------------------
// Máquina de estados del blindaje
// Se llama continuamente desde loop()
// -----------------------------------------------------------
void updateShieldAction() {
    if (SHIELD_STATE == 0) return;

    // FSM: apertura
    if (SHIELD_STATE == 1) {
        if (digitalRead(SENS_GREEN)) {
            digitalWrite(RLY_DOOR_OPEN, LOW);
            SHIELD_STATE = 0;
            Serial.println("Shield fully opened.");
            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SHIELD_OPEN);
                SerialNodeMaster.print('\r');
                Serial.println(">> ACK sent: STATE_SHIELD_OPEN");
            }
        }
    }

    // FSM: cierre
    else if (SHIELD_STATE == 2) {
        if (digitalRead(SENS_BLUE)) {
            digitalWrite(RLY_DOOR_CLOSE, LOW);
            SHIELD_STATE = 0;
            Serial.println("Shield fully closed.");
            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_SHIELD_CLOSED);
                SerialNodeMaster.print('\r');
                Serial.println(">> ACK sent: STATE_SHIELD_CLOSE");
            }
        }
    }

    // Timeout general
    if (millis() - shieldStartTime > SHIELD_TIMEOUT_MS) {
        digitalWrite(RLY_DOOR_OPEN, LOW);
        digitalWrite(RLY_DOOR_CLOSE, LOW);
        SHIELD_STATE = 0;
        Serial.println("Shield movement timeout.");
        if (currentReplyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(6);  // Código de error: timeout en blindaje
            SerialNodeMaster.print('\r');
        }
    }
}
