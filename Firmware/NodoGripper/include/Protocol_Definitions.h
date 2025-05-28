#ifndef PROTOCOL_DEFINITIONS_H
#define PROTOCOL_DEFINITIONS_H

// ======================================================================
// GENERAL (comunes a todos los nodos)
// ======================================================================

#define CMD_TERMINATOR     '\r'    // Delimitador de fin de comando

// Caracteres de respuesta estándar
#define RESP_ACK           'K'     // Comando ejecutado correctamente
#define RESP_ERROR         'E'     // Error durante ejecución

// Estados del protocolo de recepción
#define PROTOCOL_IDLE           0
#define PROTOCOL_READING_CMD    1
#define PROTOCOL_READING_ARG    2
#define PROTOCOL_COMPLETE       3

// Comandos generales del sistema
#define CMD_ABORT          'X'     // Parada de emergencia
#define CMD_PING           'T'     // Test de conexión (ping)


/* =====================================================================
 * NODO WHEEL: control de mesa, blindaje y ruleta de muestras
 * ===================================================================== */

// Comandos
#define CMD_SAMPLE_WHEEL   'S'     // Seleccionar siguiente muestra (ruleta)
#define CMD_SHIELD         'H'     // Control del blindaje (0 cerrar, 1 abrir)
#define CMD_PLATE          'P'     // Control de la mesa (0 subir, 1 bajar)

// Argumentos válidos
#define ARG_SAMPLE_NEXT          0  // (por expansión futura)

#define ARG_SHIELD_CLOSE         0
#define ARG_SHIELD_OPEN          1

#define ARG_PLATE_UP             0
#define ARG_PLATE_DOWN           1


/* =====================================================================
 * NODO GRIPPER: control del actuador de garra y eje Z vertical
 * ===================================================================== */

// Comandos
#define CMD_GRIPPER        'G'     // Control de garra (0 cerrar, 1 abrir)
#define CMD_ZAXIS          'Z'     // Control de posición vertical

// Argumentos válidos
#define ARG_GRIPPER_CLOSE        0
#define ARG_GRIPPER_OPEN         1

#define ARG_ZAXIS_POS1           0  // Posición inferior
#define ARG_ZAXIS_POS2           1  // Posición intermedia
#define ARG_ZAXIS_POS3           2  // Posición superior


/* =====================================================================
 * NODO MAESTRO: comandos internos de coordinación o prueba
 * ===================================================================== */

// Comandos especiales (pueden ser interpretados por todos)
#define CMD_MASTER_READY    'R'   // Señal de reinicio o coordinación (opcional)

#endif // PROTOCOL_DEFINITIONS_H
