#ifndef ZAXIS_CONTROL_H
#define ZAXIS_CONTROL_H

// ==============================
// Constantes de estados internos
// ==============================
#define FLAG_STOP         0
#define FLAG_GO_POS_01    1
#define FLAG_GO_POS_02    2
#define FLAG_GO_POS_03    3

// ==============================
// Dirección del motor paso a paso
// ==============================
#define DIR_DOWN   LOW   // Baja el eje
#define DIR_UP     HIGH  // Sube el eje

// ==============================
// Prototipos de funciones
// ==============================

void initZAxis();
void moveZAxisToPosition(int posFlag);
int processZAxis();
void disableZAxisMotor();
void MoveOneStep();
void SoundBeepAtention();

#endif // ZAXIS_CONTROL_H
