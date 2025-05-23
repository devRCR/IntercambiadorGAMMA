#ifndef PLATE_CONTROL_H
#define PLATE_CONTROL_H

// Inicia el movimiento de la mesa según el comando
void processPlateCommand(int value, bool replyToMaster);

// Función de actualización periódica (loop)
void updatePlateMovement();

#endif
