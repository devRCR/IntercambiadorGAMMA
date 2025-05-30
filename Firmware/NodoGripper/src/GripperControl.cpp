#include <Arduino.h>
#include "GripperControl.h"
#include "Hardware_GripperNode.h"
#include "LCD_Display.h"
#include "Protocol_States.h"

// Tiempo máximo de espera para que se confirme el estado mecánico (ms)
#define GRIPPER_TIMEOUT_MS 3000

// Inicializa los pines y estado del gripper
void initGripper() {
    pinMode(PIN_GRIPPER_RELAY, OUTPUT);
    digitalWrite(PIN_GRIPPER_RELAY, LOW); // Garra desactivada por defecto

    pinMode(PIN_GRIPPER_SENSOR_OPEN, INPUT_PULLUP);
    pinMode(PIN_GRIPPER_SENSOR_CLOSED, INPUT_PULLUP);
}

// Apertura de la garra
bool openGripper() {
    lcd.clear();
    lcd.print("Opening Gripper...");

    digitalWrite(PIN_GRIPPER_RELAY, HIGH);
    delay(300);  // Activación breve del relé
    digitalWrite(PIN_GRIPPER_RELAY, LOW);

    unsigned long t_start = millis();
    while (millis() - t_start < GRIPPER_TIMEOUT_MS) {
        if (isGripperOpen()) {
            lcd.clear();
            lcd.print("Gripper OPEN");
            beep();
            return true;
        }
    }

    lcd.clear();
    lcd.print("ERROR: OPEN FAIL");
    beepError();
    return false;
}

// Cierre de la garra
bool closeGripper() {
    lcd.clear();
    lcd.print("Closing Gripper...");

    digitalWrite(PIN_GRIPPER_RELAY, HIGH);
    delay(300);  // Activación breve del relé
    digitalWrite(PIN_GRIPPER_RELAY, LOW);

    unsigned long t_start = millis();
    while (millis() - t_start < GRIPPER_TIMEOUT_MS) {
        if (isGripperClosed()) {
            lcd.clear();
            lcd.print("Gripper CLOSED");
            beep();
            return true;
        }
    }

    lcd.clear();
    lcd.print("ERROR: CLOSE FAIL");
    beepError();
    return false;
}

// Sensor: ¿la garra está abierta?
bool isGripperOpen() {
    return digitalRead(PIN_GRIPPER_SENSOR_OPEN) == HIGH;
}

// Sensor: ¿la garra está cerrada?
bool isGripperClosed() {
    return digitalRead(PIN_GRIPPER_SENSOR_CLOSED) == HIGH;
}
