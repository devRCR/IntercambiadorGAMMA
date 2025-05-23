#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

// Ejecuta el comando recibido, validado previamente por el parser.
// Llama internamente a los módulos de control según el tipo de acción.
void executeCommand(char cmd, int val);

#endif
