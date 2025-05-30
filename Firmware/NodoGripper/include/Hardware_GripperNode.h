#ifndef HARDWARE_GRIPPERNODE_H
#define HARDWARE_GRIPPERNODE_H

#include <Arduino.h>

// =====================================================================
// PUERTOS SERIALES
// =====================================================================
#define SerialNodeMaster     Serial1  // Comunicación con Nodo Maestro

// =====================================================================
// PANTALLA LCD (modo 4 bits)
// =====================================================================
#define LCD_RS    43
#define LCD_RW    44
#define LCD_EN    45
#define LCD_D4    50
#define LCD_D5    51
#define LCD_D6    52
#define LCD_D7    53

// =====================================================================
// MOTOR PASO A PASO (HUSILLO - EJE Z)
// =====================================================================
#define M_STEP    A3   // Pulso de paso
#define M_DIR     A2   // Dirección
#define M_EN      A1   // Enable (activo en bajo)

// Direcciones
#define DIR_UP        HIGH
#define DIR_DOWN      LOW

// =====================================================================
// VELOCIDAD VARIABLE (opcional, si se conecta potenciómetro)
// =====================================================================
#define SENS_SPEED   A4

// =====================================================================
// RELÉ Y BUZZER
// =====================================================================
#define PIN_GRIPPER_RELAY     A0
#define BUZZER                42

// =====================================================================
// SENSORES DE POSICIÓN DEL EJE Z (HUSILLO)
// =====================================================================
#define SENS_POS1   12  // Posición inferior
#define SENS_POS2   11  // Posición intermedia
#define SENS_POS3   10  // Posición superior

// =====================================================================
// SENSORES DE GARRA (CLAW/MARINELLI)
// =====================================================================
#define PIN_GRIPPER_SENSOR_OPEN     35  // Sensor magnético: garra abierta
#define PIN_GRIPPER_SENSOR_CLOSED   36  // Sensor magnético: garra cerrada

#define SENS_RING01  A8  // Anillo inferior sensor 1
#define SENS_RING02  A9  // Anillo inferior sensor 2
#define SENS_RING03  A10 // Anillo inferior sensor 3

#define PIN_MARI_SENSOR_1  A5  // Sensor marinelli 1
#define PIN_MARI_SENSOR_2  A6  // Sensor marinelli 2
#define PIN_MARI_SENSOR_3  A7  // Sensor marinelli 3

// =====================================================================
// BOTONES DE CONTROL DE GARRA (superior/inferior)
// =====================================================================
#define PIN_BTN_GRIPPER_CATCH_TOP      22
#define PIN_BTN_GRIPPER_RELEASE_TOP    23
#define PIN_BTN_GRIPPER_CATCH_BOTTOM   24
#define PIN_BTN_GRIPPER_RELEASE_BOTTOM 25

// =====================================================================
// BOTONES DE POSICIÓN EJE Z
// =====================================================================
#define PIN_BTN_GO_POS1   27
#define PIN_BTN_GO_POS2   28
#define PIN_BTN_GO_POS3   29
#define PIN_BTN_STOP      30  // Parada de emergencia

// =====================================================================
// BOTONES GENERALES / EXPANSIÓN
// =====================================================================
#define PIN_BTN_GENERAL1  38
#define PIN_BTN_GENERAL2  39
#define PIN_BTN_GENERAL3  40
#define PIN_BTN_GENERAL4  41

// =====================================================================
// JUMPERS (expansión futura)
// =====================================================================
#define PIN_JUMPER1   A12
#define PIN_JUMPER2   A12
#define PIN_JUMPER3   A12
#define PIN_JUMPER4   A12

#endif  // HARDWARE_GRIPPERNODE_H
