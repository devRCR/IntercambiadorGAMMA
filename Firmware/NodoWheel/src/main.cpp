#include <Arduino.h>

// Encabezados del sistema
#include "Hardware_NodeWheel.h"
#include "CommandParser.h"
#include "CommandExecutor.h"

// Controladores modulares
#include "PlateControl.h"
#include "ShieldControl.h"
#include "SampleControl.h"

// -----------------------------------------------
// Configuración inicial del sistema
// -----------------------------------------------
void setup() {
    Serial.begin(115200);             // Comunicación local (PC)
    SerialNodeMaster.begin(9600);     // Comunicación con el Nodo Maestro

    configurePins_NodeWheel();

    // Mensaje inicial
    Serial.println("Wheel Node ready.");
}

// -----------------------------------------------
// Bucle principal de control
// -----------------------------------------------
void loop() {
    // Serial.print("BOTTOM1: ");
    // Serial.print(digitalRead(SENSOR_BOTTOM1));
    // Serial.print("  BOTTOM2: ");
    // Serial.print(digitalRead(SENSOR_BOTTOM2));
    // Serial.print("  TOP1: ");
    // Serial.print(digitalRead(SENSOR_TOP1));
    // Serial.print("  TOP2: ");
    // Serial.print(digitalRead(SENSOR_TOP2));
    // Serial.print("  SHIELD OPENED: ");
    // Serial.print(digitalRead(SENS_GREEN));
    // Serial.print("  SHIELD CLOSED: ");
    // Serial.println(digitalRead(SENS_BLUE));
    // delay(500);

    // 1. Revisión de comandos desde Maestro o PC
    if (checkLineFromMaster() || checkLineFromLocal()) {
        executeCommand(getParsedCommand(), getParsedValue());
    }

    // 2. Actualización de procesos en ejecución
    updatePlateMovement();
    updateShieldAction();
    updateSampleAdvance();
}
