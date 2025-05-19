#ifndef WHEEL_COMM_H
#define WHEEL_COMM_H

void initWheelComm();
void sendToWheel(char cmd, int val);
void checkAckFromWheel();

#endif
