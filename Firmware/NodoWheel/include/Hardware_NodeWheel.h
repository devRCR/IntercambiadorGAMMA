#ifndef HARDWARE_NODEWHEEL_H
#define HARDWARE_NODEWHEEL_H

#include <Arduino.h>    

// UART para comunicación con el Nodo Maestro
#define SerialNodeMaster Serial2

// ----------------------------
// Botones físicos (Inputs)
// ----------------------------
#define BTN_NEXT     3   // Avance de muestra manual
#define BTN_CYCLE    4   // Retorno a posición base (no implementado)
#define BTN_UP       5   // Subir mesa
#define BTN_DOWN     6   // Bajar mesa
#define BTN_OPEN     11  // Abrir tapa del blindaje
#define BTN_CLOSE    12  // Cerrar tapa del blindaje

// ----------------------------
// Relevadores de control (Outputs)
// ----------------------------
#define RLY_SAMPLE_NEXT   31  // Avance de muestra
#define RLY_DOOR_OPEN     32  // Abrir blindaje
#define RLY_DOOR_CLOSE    33  // Cerrar blindaje

// ----------------------------
// Motor de la mesa (Outputs)
// ----------------------------
#define DRIVER_IN1   24
#define DRIVER_IN2   25
#define MOTOR_PWM    9

// ----------------------------
// Sensores de posición (Inputs)
// ----------------------------
#define SENSOR_BOTTOM1   22
#define SENSOR_BOTTOM2   23
#define SENSOR_TOP1      26
#define SENSOR_TOP2      27
#define SENS_ORANGE      28   // Sensor de avance de muestra
#define SENS_BLUE        29   // Blindaje cerrado
#define SENS_GREEN       30   // Blindaje abierto

// ----------------------------
// Alarma sonora
// ----------------------------
#define BUZZER        8

// ----------------------------
// Configuración de pines (debe llamarse desde setup si se desea modularizar)
// ----------------------------
inline void configurePins_NodeWheel() {
    // Botones
    pinMode(BTN_NEXT, INPUT_PULLUP);
    pinMode(BTN_CYCLE, INPUT_PULLUP);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_OPEN, INPUT_PULLUP);
    pinMode(BTN_CLOSE, INPUT_PULLUP);

    // Relevadores
    pinMode(RLY_SAMPLE_NEXT, OUTPUT);
    pinMode(RLY_DOOR_OPEN, OUTPUT);
    pinMode(RLY_DOOR_CLOSE, OUTPUT);

    // Motor
    pinMode(DRIVER_IN1, OUTPUT);
    pinMode(DRIVER_IN2, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);

    // Sensores
    pinMode(SENSOR_BOTTOM1, INPUT_PULLUP);
    pinMode(SENSOR_BOTTOM2, INPUT_PULLUP);
    pinMode(SENSOR_TOP1, INPUT_PULLUP);
    pinMode(SENSOR_TOP2, INPUT_PULLUP);
    pinMode(SENS_ORANGE, INPUT_PULLUP);
    pinMode(SENS_BLUE, INPUT_PULLUP);
    pinMode(SENS_GREEN, INPUT_PULLUP);

    // Buzzer
    pinMode(BUZZER, OUTPUT);
}

#endif
