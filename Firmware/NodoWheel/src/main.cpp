/**
 * @file main.cpp
 * @brief Main entry point for the NodoWheel firmware.
 *
 * This file initializes the hardware and manages the main control loop for the Wheel Node.
 * It handles communication with the master node and local PC, processes incoming commands,
 * and updates the state of modular controllers for plate, shield, and sample mechanisms.
 *
 * Included Modules:
 * - Hardware_NodeWheel: Hardware abstraction and pin configuration.
 * - CommandParser: Parsing of incoming command strings.
 * - CommandExecutor: Execution of parsed commands.
 * - PlateControl: Control logic for plate movement.
 * - ShieldControl: Control logic for shield mechanism.
 * - SampleControl: Control logic for sample advancement.
 *
 * Main Functions:
 * - setup(): Initializes serial communication, configures hardware pins, and prints a startup message.
 * - loop(): Main control loop that checks for incoming commands and updates the state of all subsystems.
 */
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
    Serial.print("BOTTOM1: ");
    Serial.print(digitalRead(SENSOR_BOTTOM1));
    Serial.print("  BOTTOM2: ");
    Serial.print(digitalRead(SENSOR_BOTTOM2));
    Serial.print("  TOP1: ");
    Serial.print(digitalRead(SENSOR_TOP1));
    Serial.print("  TOP2: ");
    Serial.print(digitalRead(SENSOR_TOP2));
    Serial.print("  SHIELD OPENED: ");
    Serial.print(digitalRead(SENS_GREEN));
    Serial.print("  SHIELD CLOSED: ");
    Serial.print(digitalRead(SENS_BLUE));
    Serial.print("  NEXT SAMPLE: ");
    Serial.println(digitalRead(SENS_ORANGE));
    delay(500);

    // 1. Revisión de comandos desde Maestro o PC
    if (checkLineFromMaster() || checkLineFromLocal()) {
        executeCommand(getParsedCommand(), getParsedValue());
    }

    // 2. Actualización de procesos en ejecución
    updatePlateMovement();
    updateShieldAction();
    updateSampleAdvance();
}
