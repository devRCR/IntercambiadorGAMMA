#ifndef PROTOCOL_STATES_H
#define PROTOCOL_STATES_H

// =====================================================================
// ESTADOS GENERALES (000–099)
// =====================================================================
#define STATE_UNKNOWN               0
#define STATE_IDLE                 10
#define STATE_BUSY                 11
#define STATE_READY                12
#define STATE_ERROR                13
#define STATE_EMERGENCY_STOP       99

// =====================================================================
// NODO WHEEL (100–199)
// =====================================================================
#define STATE_SAMPLE_NEXT         100
#define STATE_SAMPLE_CYCLE        110

#define STATE_SHIELD_CLOSED       120
#define STATE_SHIELD_OPEN         121

#define STATE_PLATE_DOWN          130
#define STATE_PLATE_UP            131

// =====================================================================
// NODO GRIPPER (200–299)
// =====================================================================
#define STATE_GRIPPER_OPEN        200
#define STATE_GRIPPER_CLOSED      201

#define STATE_ZAXIS_POS1          210   // Abajo
#define STATE_ZAXIS_POS2          211   // Medio
#define STATE_ZAXIS_POS3          212   // Arriba
#define STATE_ZAXIS_BASE          210   // Para indexar

// =====================================================================
// NODO MAESTRO (300–399)
// =====================================================================
#define STATE_MASTER_READY        300
#define STATE_MASTER_BUSY         301
#define STATE_MASTER_ABORT        302

// =====================================================================
// CÓDIGOS DE ERROR (400–499)
// =====================================================================
#define ERROR_UNKNOWN_COMMAND     400
#define ERROR_INVALID_ARGUMENT    401 
#define ERROR_TIMEOUT_PLATE       410
#define ERROR_TIMEOUT_SHIELD      411
#define ERROR_TIMEOUT_WHEEL       412

#define ERROR_TIMEOUT_GRIPPER     420
#define ERROR_TIMEOUT_ZAXIS       421
#define ERROR_GRIPPER_BLOCKED     422
#define ERROR_INVALID_SEQUENCE    430
#define ERROR_SHIELD_NOT_CLOSED   440
#define ERROR_PLATE_NOT_DOWN      441

// =====================================================================
// RESERVAS PARA SENSORES / NODOS FUTUROS (500–599)
// =====================================================================
// #define STATE_SENSOR_OK        500
// #define STATE_SENSOR_FAIL      501

#endif // PROTOCOL_STATES_H
