#ifndef SHIELD_CONTROL_H
#define SHIELD_CONTROL_H

void startShieldAction(int action); // 0: abrir, 1: cerrar
void updateShieldAction();          // se llama desde loop()

#endif
