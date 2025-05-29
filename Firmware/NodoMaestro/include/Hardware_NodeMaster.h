#ifndef HARDWARE_NODEMASTER_H
#define HARDWARE_NODEMASTER_H

// =====================================================
// CONFIGURACIÓN DE PINES PARA NODO MAESTRO
// Proyecto: Sistema automatizado para espectrometría gamma
// =====================================================

// -----------------------------------------------------
// BOTONES ASOCIADOS AL NODO WHEEL
// -----------------------------------------------------
#define PIN_BTN_SAMPLE_NEXT       30   // Avanzar ruleta (S0)
#define PIN_BTN_SAMPLE_PREV       31   // [Reservado / sin uso actual]
#define PIN_BTN_PLATE_DOWN        32   // Bajar mesa (P1)
#define PIN_BTN_PLATE_UP          33   // Subir mesa (P0)
#define PIN_BTN_SHIELD_OPEN       34   // Abrir blindaje (H1)
#define PIN_BTN_SHIELD_CLOSE      35   // Cerrar blindaje (H0)

// -----------------------------------------------------
// BOTONES ASOCIADOS AL NODO GRIPPER
// -----------------------------------------------------
#define PIN_BTN_STOP              36   // Parada de emergencia (X0)
#define PIN_BTN_GO_POS_1          37   // Ir a posición Z1 (Z0)
#define PIN_BTN_GO_POS_2          38   // Ir a posición Z2 (Z1)
#define PIN_BTN_GO_POS_3          39   // Ir a posición Z3 (Z2)
#define PIN_BTN_GRIPPER_CATCH     40   // Cerrar garra (G0)
#define PIN_BTN_GRIPPER_RELEASE   41   // Abrir garra (G1)

// -----------------------------------------------------
// BOTONES GENERALES / FUNCIONES ESPECIALES
// -----------------------------------------------------
#define PIN_BTN_SEQUENCE_START    45   // Iniciar secuencia automática (por implementar)

// -----------------------------------------------------
// PUERTOS SERIALES (alias)
// -----------------------------------------------------
#define SerialGUI         Serial      // Comunicación con GUI externa
#define SerialNodeWheel   Serial1     // Comunicación con Nodo Wheel
#define SerialNodeGripper Serial2     // Comunicación con Nodo Gripper

#endif // HARDWARE_NODEMASTER_H
