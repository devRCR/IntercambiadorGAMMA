#include <Arduino.h>
#include "Hardware_GripperNode.h"
#include "CommandParser.h"
#include "CommandExecutor.h"
#include "GripperControl.h"
#include "ZAxisControl.h"
#include "LCD_Display.h"
#include "Buttons.h"

// Tiempo para revisar botones y timeout de comandos
#define LOOP_PERIOD_MS 20
unsigned long lastLoopTime = 0;

void setup()
{
    // Inicializa puertos seriales
    Serial.begin(115200);         // Interfaz para pruebas
    SerialNodeMaster.begin(9600); // Comunicación con Nodo Maestro

    // Inicializa periféricos del sistema
    initGripper(); // Motores, sensores y relé del gripper
    initZAxis();   // Motor paso a paso, sensores de eje Z
    initLCD();     // Pantalla LCD
    initButtons(); // Botonera local

    // Mensaje inicial
    lcd.setCursor(0, 0);
    lcd.print("Nodo Gripper listo");
    delay(1000);
    lcd.clear();
}

void loop()
{
    // 1. Revisión de comandos desde Maestro o desde PC
    if (checkLineFromMaster() || checkLineFromLocal()) {
        executeCommand(getParsedCommand(), getParsedValue());
    }

    // 2. Procesamiento de botones físicos
    checkButtons();
}
