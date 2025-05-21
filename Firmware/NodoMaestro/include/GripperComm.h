#ifndef GRIPPER_COMM_H
#define GRIPPER_COMM_H

bool checkAckFromGripper();
void initGripperComm();
void sendToGripper(char cmd, int val);

#endif

