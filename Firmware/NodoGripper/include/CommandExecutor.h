#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

void executeCommand(char cmd, int val);
void abortAllActions();

void sendACK(int state);
void sendERR(int code);

#endif
