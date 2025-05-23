#include <Arduino.h>
#include "PlateControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"

// -------------------------------
// Variables internas de control
// -------------------------------

#define DIR_UP    0
#define DIR_DOWN  1

static uint8_t RUNNING = 0;                  // 0: inactivo, 1: bajando, 2: subiendo
static unsigned long startTime = 0;
static const unsigned long TIMEOUT_MS = 15000;
static bool currentReplyToMaster = false;    // Solo si comando proviene del maestro

// ------------------------------------------------------
// Inicia el movimiento de la mesa niveladora
// value = 0 (subir), 1 (bajar)
// replyToMaster = true → enviar ACK/ERROR al maestro
// ------------------------------------------------------
void processPlateCommand(int value, bool replyToMaster) {
    if (RUNNING != 0) {
        Serial.println("Plate already moving.");
        return;
    }

    currentReplyToMaster = replyToMaster;

    if (value == DIR_DOWN) {
        if (digitalRead(SENSOR_BOTTOM1) && digitalRead(SENSOR_BOTTOM2)) {
            Serial.println("Plate already at bottom.");
            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_PLATE_DOWN);
                SerialNodeMaster.print('\r');
            }
            return;
        }

        Serial.println("Starting plate down...");
        digitalWrite(DRIVER_IN1, LOW);
        digitalWrite(DRIVER_IN2, HIGH);
        analogWrite(MOTOR_PWM, 150);
        RUNNING = 1;
        startTime = millis();

    } else if (value == DIR_UP) {
        if (digitalRead(SENSOR_TOP1) && digitalRead(SENSOR_TOP2)) {
            Serial.println("Plate already at top.");
            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_PLATE_UP);
                SerialNodeMaster.print('\r');
            }
            return;
        }

        Serial.println("Starting plate up...");
        digitalWrite(DRIVER_IN1, HIGH);
        digitalWrite(DRIVER_IN2, LOW);
        analogWrite(MOTOR_PWM, 150);
        RUNNING = 2;
        startTime = millis();

    } else {
        Serial.println("Invalid plate command value.");
    }
}

// ------------------------------------------------------
// Máquina de estados del movimiento de la mesa
// Se llama continuamente desde loop()
// ------------------------------------------------------
void updatePlateMovement() {
    if (RUNNING == 0) return;

    // FSM: Bajar mesa
    if (RUNNING == 1) {
        if (digitalRead(SENSOR_BOTTOM1) && digitalRead(SENSOR_BOTTOM2)) {
            analogWrite(MOTOR_PWM, 0);
            RUNNING = 0;
            Serial.println("Plate reached bottom.");

            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_PLATE_DOWN);
                SerialNodeMaster.print('\r');
            }
        }
    }

    // FSM: Subir mesa
    else if (RUNNING == 2) {
        if (digitalRead(SENSOR_TOP1) && digitalRead(SENSOR_TOP2)) {
            analogWrite(MOTOR_PWM, 0);
            RUNNING = 0;
            Serial.println("Plate reached top.");

            if (currentReplyToMaster) {
                SerialNodeMaster.print('K');
                SerialNodeMaster.print(STATE_PLATE_UP);
                SerialNodeMaster.print('\r');
            }
        }
    }

    // Verificar timeout
    if (millis() - startTime > TIMEOUT_MS) {
        analogWrite(MOTOR_PWM, 0);
        RUNNING = 0;
        Serial.println("Plate movement timeout.");

        if (currentReplyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(1);  // Código de error: timeout
            SerialNodeMaster.print('\r');
        }
    }
}
