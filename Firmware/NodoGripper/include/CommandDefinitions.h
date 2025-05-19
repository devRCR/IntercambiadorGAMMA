#ifndef COMMAND_DEFINITIONS_H
#define COMMAND_DEFINITIONS_H

// Comandos del protocolo
#define CMD_GRIPPER    'G'   // Captura o liberación
#define CMD_POSITION   'Y'   // Movimiento vertical (husillo)
#define CMD_STOP       'T'   // Emergencia

// Valores para el gripper
#define VAL_RELEASE     0
#define VAL_CATCH       1

// Posiciones verticales
#define VAL_POS_Y1      1
#define VAL_POS_Y2      2
#define VAL_POS_Y3      3

// Valor de parada
#define VAL_STOP        0

#endif
