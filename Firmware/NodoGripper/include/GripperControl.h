#ifndef GRIPPER_CONTROL_H
#define GRIPPER_CONTROL_H


// Inicializa los pines y estado del gripper
// Configura pines de control, sensores y estado inicial
void initGripper();

// Ejecuta acciones y devuelve éxito/fallo
bool openGripper();
bool closeGripper();

// Sensores de estado
bool isGripperOpen();
bool isGripperClosed();

#endif
