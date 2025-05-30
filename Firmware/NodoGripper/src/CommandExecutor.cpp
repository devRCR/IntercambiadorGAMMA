#include "CommandExecutor.h"
#include "Protocol_Definitions.h"
#include "Hardware_GripperNode.h"
#include "Protocol_States.h"
#include "ZAxisControl.h"
#include "GripperControl.h"
#include "LCD_Display.h"

// --------------------------------------------------
// Envía ACK con código de estado exitoso
// --------------------------------------------------
void sendACK(int state) {
    SerialNodeMaster.print(RESP_ACK);  // 'K'
    SerialNodeMaster.print(state);
    SerialNodeMaster.print(CMD_TERMINATOR);  // '\r'
}

// --------------------------------------------------
// Envía mensaje de error con código
// --------------------------------------------------
void sendERR(int code) {
    SerialNodeMaster.print(RESP_ERROR);  // 'E'
    SerialNodeMaster.print(code);
    SerialNodeMaster.print(CMD_TERMINATOR);  // '\r'
}

// --------------------------------------------------
// Ejecuta el comando recibido desde GUI o botones
// --------------------------------------------------
void executeCommand(char cmd, int val) {
    switch (cmd) {

        // ------------------------------------------
        // Control del eje Z vertical
        // ------------------------------------------
        case CMD_ZAXIS:
            switch (val) {
                case ARG_ZAXIS_POS1:
                case ARG_ZAXIS_POS2:
                case ARG_ZAXIS_POS3:
                    moveZAxisToPosition(val);  // ACK se enviará internamente
                    break;
                default:
                    sendERR(ERROR_INVALID_ARGUMENT);
                    break;
            }
            break;

        // ------------------------------------------
        // Control de apertura/cierre de la garra
        // ------------------------------------------
        case CMD_GRIPPER:
            switch (val) {
                case ARG_GRIPPER_OPEN:
                    if (openGripper()) {
                        sendACK(STATE_GRIPPER_OPEN);
                    } else {
                        sendERR(ERROR_GRIPPER_BLOCKED);
                    }
                    break;

                case ARG_GRIPPER_CLOSE:
                    if (closeGripper()) {
                        sendACK(STATE_GRIPPER_CLOSED);
                    } else {
                        sendERR(ERROR_GRIPPER_BLOCKED);
                    }
                    break;

                default:
                    sendERR(ERROR_INVALID_ARGUMENT);
                    break;
            }
            break;

        // ------------------------------------------
        // Parada de emergencia
        // ------------------------------------------
        case CMD_ABORT:
            abortAllActions();
            sendACK(STATE_EMERGENCY_STOP);
            break;

        // ------------------------------------------
        // Comando inválido
        // ------------------------------------------
        default:
            sendERR(ERROR_UNKNOWN_COMMAND);
            break;
    }
}

// --------------------------------------------------
// Detiene todos los subsistemas en caso de emergencia
// --------------------------------------------------
void abortAllActions() {
    disableZAxisMotor();

    if (!isGripperOpen() && !isGripperClosed()) {
        openGripper();  // Intenta liberar muestra si está bloqueada
    }

    beepError();  // Señal audible de error
}
