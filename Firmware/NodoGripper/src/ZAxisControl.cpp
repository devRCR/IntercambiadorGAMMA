#include <Arduino.h>
#include <LiquidCrystal.h>
#include "ZAxisControl.h"
#include "Hardware_GripperNode.h"
#include "Protocol_States.h"
#include "LCD_Display.h"

// Configuración de pines para el motor paso a paso y sensores
int RUNNING_MODE = FLAG_STOP;
int DIRECTION = DIR_DOWN;
unsigned long MillisActual = 0;
int us_delay = 1200;

void initZAxis() {
    
    pinMode(M_EN, OUTPUT);
    digitalWrite(M_EN, HIGH); // Motor deshabilitado al inicio

    pinMode(M_STEP, OUTPUT);
    digitalWrite(M_STEP, HIGH); // Estado inicial del pin de paso

    pinMode(M_DIR, OUTPUT);
    digitalWrite(M_DIR, DIR_DOWN); // Dirección inicial segura

    // Sensores de posición
    pinMode(SENS_POS1, INPUT_PULLUP);
    pinMode(SENS_POS2, INPUT_PULLUP);
    pinMode(SENS_POS3, INPUT_PULLUP);

    // Sensores de anillo de protección (arriba)
    pinMode(SENS_RING01, INPUT_PULLUP);
    pinMode(SENS_RING02, INPUT_PULLUP);
    pinMode(SENS_RING03, INPUT_PULLUP);

    // Sensor de velocidad (entrada analógica)
    pinMode(SENS_SPEED, INPUT);

    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);

    lcd.begin(16, 2);
    lcd.clear();
    lcd.print("ZAxis Ready");
}

void moveZAxisToPosition(int posFlag) {
    RUNNING_MODE = posFlag;
}

int processZAxis() {
    switch (RUNNING_MODE) {
        case FLAG_GO_POS_01:
            if (!digitalRead(SENS_POS1)) {
                MillisActual = millis();
                DIRECTION = DIR_DOWN;
                digitalWrite(M_EN, LOW);
                MoveOneStep();
            } else {
                RUNNING_MODE = FLAG_STOP;
                digitalWrite(M_EN, HIGH);
                lcd.clear();
                lcd.print("POS 01 reached");
                SoundBeepAtention();
                return STATE_ZAXIS_POS1;
            }
            break;

        case FLAG_GO_POS_02:
            if (!digitalRead(SENS_POS2)) {
                MillisActual = millis();
                DIRECTION = DIR_UP;
                digitalWrite(M_EN, LOW);
                MoveOneStep();
            } else {
                RUNNING_MODE = FLAG_STOP;
                digitalWrite(M_EN, HIGH);
                lcd.clear();
                lcd.print("POS 02 reached");
                SoundBeepAtention();
                return STATE_ZAXIS_POS2;
            }
            break;

        case FLAG_GO_POS_03:
            if (!digitalRead(SENS_RING01) &&
                !digitalRead(SENS_RING02) &&
                !digitalRead(SENS_RING03)) {
                DIRECTION = DIR_UP;
                digitalWrite(M_EN, LOW);
                MoveOneStep();
            } else {
                RUNNING_MODE = FLAG_STOP;
                digitalWrite(M_EN, HIGH);
                lcd.clear();
                lcd.print("Marinelli on");
                lcd.setCursor(0, 1);
                lcd.print("detector");
                SoundBeepAtention();
                return STATE_ZAXIS_POS3;
            }
            break;
    }

    return -1;
}

void disableZAxisMotor() {
    digitalWrite(M_EN, HIGH);
}

void MoveOneStep() {
    digitalWrite(M_DIR, DIRECTION);
    digitalWrite(M_STEP, LOW);
    delayMicroseconds(500);
    digitalWrite(M_STEP, HIGH);
    delayMicroseconds(us_delay);
}

void SoundBeepAtention() {
    digitalWrite(BUZZER, HIGH);
    delay(100);
    digitalWrite(BUZZER, LOW);
}
