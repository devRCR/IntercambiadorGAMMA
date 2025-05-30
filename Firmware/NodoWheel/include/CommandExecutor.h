#ifndef COMMAND_EXECUTOR_H
#define COMMAND_EXECUTOR_H

// Ejecuta el comando recibido, validado previamente por el parser.
// Llama internamente a los módulos de control según el tipo de acción.
void executeCommand(char cmd, int val);
// Envía un mensaje de reconocimiento (ACK) al Nodo Maestro
// El estado puede ser uno de los definidos en Protocol_States.h
void sendACK(int state) ;
// Envia un mensaje de error con el código especificado
// El estado puede ser uno de los definidos en Protocol_States.h
void sendERR(int code);


#endif
