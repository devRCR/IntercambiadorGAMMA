#include <Arduino.h>
#include "Hardware_NodeWheel.h"
#include "CommandParser.h"
#include "CommandExecutor.h"

void setup() {
    Serial.begin(115200);             // Para monitoreo por USB
    SerialNodeMaster.begin(9600);     // Comunicación con el Nodo Maestro

    Serial.println("Nodo Wheel listo.");
}

void loop() {
    if (checkLineFromMaster()) {
        executeCommand(getParsedCommand(), getParsedValue());
    }
}
