#ifndef HARDWARE_NODEWHEEL_H
#define HARDWARE_NODEWHEEL_H

#include <Arduino.h>

// =====================================================
// CONFIGURACIÓN DE HARDWARE - NODO WHEEL
// Proyecto: Sistema automatizado para espectrometría gamma
// =====================================================

// -----------------------------------------------------
// PUERTO SERIAL DE COMUNICACIÓN CON NODO MAESTRO
// -----------------------------------------------------
#define SerialNodeMaster Serial2

// -----------------------------------------------------
// ENTRADAS DIGITALES - BOTONES FÍSICOS
// -----------------------------------------------------
#define BTN_NEXT     3    // Avanzar ruleta de muestras
#define BTN_CYCLE    4    // Ciclo/reset (no implementado)
#define BTN_UP       5    // Subir mesa elevadora
#define BTN_DOWN     6    // Bajar mesa elevadora
#define BTN_OPEN     11   // Abrir tapa del blindaje
#define BTN_CLOSE    12   // Cerrar tapa del blindaje

// -----------------------------------------------------
// SALIDAS DIGITALES - RELEVADORES DE CONTROL
// -----------------------------------------------------
#define RLY_DOOR_OPEN      46   // Activa apertura de blindaje
#define RLY_DOOR_CLOSE     47   // Activa cierre de blindaje
#define RLY_SAMPLE_NEXT    48   // Activa avance de ruleta

// -----------------------------------------------------
// CONTROL DE MOTOR DE LA MESA ELEVADORA
// -----------------------------------------------------
#define DRIVER_IN1   A1   // Dirección A (driver)
#define DRIVER_IN2   A0   // Dirección B (driver)
#define MOTOR_PWM    2    // Velocidad (PWM)

// -----------------------------------------------------
// ENTRADAS DIGITALES - SENSORES DE POSICIÓN
// -----------------------------------------------------
#define SENSOR_TOP1       40   // Sensor límite superior 1
#define SENSOR_TOP2       41   // Sensor límite superior 2
#define SENSOR_BOTTOM1    42   // Sensor límite inferior 1
#define SENSOR_BOTTOM2    43   // Sensor límite inferior 2

#define SENS_ORANGE       7    // Sensor avance de ruleta (N/A)
#define SENS_VIOLET       8    // [Reservado]
#define SENS_GREEN        9    // Blindaje completamente abierto
#define SENS_BLUE         10   // Blindaje completamente cerrado

// -----------------------------------------------------
// SALIDA DIGITAL - ALARMA SONORA
// -----------------------------------------------------
#define BUZZER            A2   // Buzzer de advertencia

// -----------------------------------------------------
// CONFIGURACIÓN DE PINES (invocar desde setup())
// -----------------------------------------------------
inline void configurePins_NodeWheel() {
    // Botones físicos
    pinMode(BTN_NEXT, INPUT_PULLUP);
    pinMode(BTN_CYCLE, INPUT_PULLUP);
    pinMode(BTN_UP, INPUT_PULLUP);
    pinMode(BTN_DOWN, INPUT_PULLUP);
    pinMode(BTN_OPEN, INPUT_PULLUP);
    pinMode(BTN_CLOSE, INPUT_PULLUP);

    // Relevadores de control
    pinMode(RLY_SAMPLE_NEXT, OUTPUT);
    pinMode(RLY_DOOR_OPEN, OUTPUT);
    pinMode(RLY_DOOR_CLOSE, OUTPUT);

    // Motor de la mesa
    pinMode(DRIVER_IN1, OUTPUT);
    pinMode(DRIVER_IN2, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);

    // Sensores de posición
    pinMode(SENSOR_BOTTOM1, INPUT_PULLUP);
    pinMode(SENSOR_BOTTOM2, INPUT_PULLUP);
    pinMode(SENSOR_TOP1, INPUT_PULLUP);
    pinMode(SENSOR_TOP2, INPUT_PULLUP);
    pinMode(SENS_ORANGE, INPUT_PULLUP);
    pinMode(SENS_BLUE, INPUT_PULLUP);
    pinMode(SENS_GREEN, INPUT_PULLUP);
    pinMode(SENS_VIOLET, INPUT_PULLUP);  // Mantener declarado si está conectado

    // Buzzer
    pinMode(BUZZER, OUTPUT);
}

#endif // HARDWARE_NODEWHEEL_H
