#ifndef PROTOCOL_DEFINITIONS_H
#define PROTOCOL_DEFINITIONS_H

// ===========================================
// PUERTOS SERIALES DEL NODO MAESTRO
// ===========================================
#define SerialGUI     Serial     // Comunicación con interfaz GUI (USB)
#define SerialWheel   Serial2    // Comunicación con Nodo Wheel
#define SerialGripper Serial1    // Comunicación con Nodo Gripper (antes Spindle)

// ===========================================
// COMANDOS PARA NODO WHEEL
// ===========================================
#define CMD_SHIELD    'H'  // Blindaje del detector
#define CMD_PLATE     'P'  // Mesa niveladora
#define CMD_SAMPLE    'S'  // Rueda de muestras

// Valores binarios estándar
#define VAL_OPEN       0
#define VAL_CLOSE      1

// Acciones del blindaje
#define VAL_SHIELD_OPEN     VAL_OPEN
#define VAL_SHIELD_CLOSE    VAL_CLOSE

// Acciones de la mesa niveladora
#define VAL_PLATE_UP        VAL_OPEN
#define VAL_PLATE_DOWN      VAL_CLOSE

// Acciones de la rueda de muestras
#define VAL_SAMPLE_CYCLE    VAL_OPEN
#define VAL_SAMPLE_NEXT     VAL_CLOSE

// ===========================================
// COMANDOS PARA NODO GRIPPER
// ===========================================
#define CMD_GRIPPER    'G'  // Captura o liberación del Marinelli
#define CMD_POSITION   'Y'  // Posicionamiento vertical del husillo
#define CMD_STOP       'T'  // Detención de emergencia

// Acciones del gripper
#define VAL_GRIPPER_RELEASE     0
#define VAL_GRIPPER_CATCH       1

// Posiciones verticales del husillo
#define VAL_POS_Y1      1
#define VAL_POS_Y2      2
#define VAL_POS_Y3      3

// Valor para parada de emergencia
#define VAL_STOP        0

#endif
