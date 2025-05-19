#ifndef GRIPPER_COMM_H
#define GRIPPER_COMM_H

void initGripperComm();
void sendToGripper(char cmd, int val);
void checkAckFromGripper();

#endif

