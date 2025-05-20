#ifndef HARDWARE_NODEMASTER_H
#define HARDWARE_NODEMASTER_H

// ===============================
// PINES DE ENTRADA (BOTONES FÍSICOS)
// ===============================

// Botones para Rueda de muestras (Wheel)
#define PIN_BTN_SAMPLE_NEXT       30
#define PIN_BTN_SAMPLE_PREV      31

// Botones para Mesa niveladora (Wheel)
#define PIN_BTN_PLATE_DOWN        32
#define PIN_BTN_PLATE_UP          33

// Botones para Blindaje del detector (Wheel)
#define PIN_BTN_SHIELD_OPEN       34
#define PIN_BTN_SHIELD_CLOSE      35

// Botón de parada de emergencia (Gripper)
#define PIN_BTN_STOP              36

// Posiciones verticales del Gripper (husillo)
#define PIN_BTN_GO_POS_1          37
#define PIN_BTN_GO_POS_2          38
#define PIN_BTN_GO_POS_3          39

// Captura y liberación de Marinelli (Gripper)
#define PIN_BTN_GRIPPER_CATCH     40
#define PIN_BTN_GRIPPER_RELEASE   41

// Inicio de secuencia automática
#define PIN_BTN_SEQUENCE_START    45

#endif
