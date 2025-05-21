#include <Arduino.h>
#include "PlateControl.h"
#include "Hardware_NodeWheel.h"
#include "Protocol_States.h"

// Parámetros de control
#define MOTOR_PWM_VALUE 200
#define TIMEOUT_MS 5000

// Procesa comando P0 (subir) o P1 (bajar)
void processPlateCommand(int value, bool replyToMaster) {
    bool finished = false;
    unsigned long startTime = millis();

    if (value == 0) {
        // Subir mesa
        Serial.println("Plate ↑ (UP)");
        digitalWrite(DRIVER_IN1, HIGH);
        digitalWrite(DRIVER_IN2, LOW);
    } else if (value == 1) {
        // Bajar mesa
        Serial.println("Plate ↓ (DOWN)");
        digitalWrite(DRIVER_IN1, LOW);
        digitalWrite(DRIVER_IN2, HIGH);
    } else {
        Serial.println("Invalid plate command");
        if (replyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(3);  // Código de error: comando inválido
            SerialNodeMaster.print('\r');
        }
        return;
    }

    analogWrite(MOTOR_PWM, MOTOR_PWM_VALUE);

    // Espera a que se activen los sensores correctos
    while (!finished && (millis() - startTime < TIMEOUT_MS)) {
        if (value == 0) { // Subir: ambos sensores superiores deben activarse
            if (digitalRead(SENSOR_TOP1) == HIGH && digitalRead(SENSOR_TOP2) == HIGH) {
                finished = true;
            }
        } else { // Bajar: ambos sensores inferiores deben activarse
            if (digitalRead(SENSOR_BOTTOM1) == HIGH && digitalRead(SENSOR_BOTTOM2) == HIGH) {
                finished = true;
            }
        }
    }

    // Detener motor
    digitalWrite(DRIVER_IN1, LOW);
    digitalWrite(DRIVER_IN2, LOW);
    analogWrite(MOTOR_PWM, 0);

    // Verificación final
    if (finished) {
        Serial.println("Plate movement complete");
        if (replyToMaster) {
            SerialNodeMaster.print('K');
            SerialNodeMaster.print(value == 0 ? STATE_PLATE_UP : STATE_PLATE_DOWN);
            SerialNodeMaster.print('\r');
        }
    } else {
        Serial.println("Plate movement timeout");
        if (replyToMaster) {
            SerialNodeMaster.print('E');
            SerialNodeMaster.print(1); // Código de error: timeout
            SerialNodeMaster.print('\r');
        }
    }
}
