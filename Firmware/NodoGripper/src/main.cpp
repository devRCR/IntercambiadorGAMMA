#include <Arduino.h>
#include "Hardware_GripperNode.h"
#include "CommandParser.h"
#include "CommandExecutor.h"

void setup() {
    Serial.begin(115200);             // Consola de monitoreo
    SerialNodeMaster.begin(9600);     // Comunicación con el Maestro

    Serial.println("GripperNode inicializado.");
}

void loop() {
    if (checkLineFromMaster()) {
        executeCommand(getParsedCommand(), getParsedValue());
    }
}
