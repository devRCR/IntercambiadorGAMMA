#ifndef SAMPLE_CONTROL_H
#define SAMPLE_CONTROL_H

void startSampleAdvance(int mode); // 0: ciclo base, 1: siguiente muestra
void updateSampleAdvance();        // se llama desde loop()

#endif
