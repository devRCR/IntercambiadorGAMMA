#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

// ============================================================================
// INTERFAZ DEL MÓDULO PARSER DE COMANDOS
// 
// Este módulo permite recibir, almacenar y consultar comandos provenientes de:
// - El puerto serial USB (Serial)
// - El Nodo Maestro (SerialNodeMaster)
// - Botones físicos conectados al microcontrolador
// El comando se analiza en formato: C[valor]\r  (por ejemplo: G0\r)
// ============================================================================


// ---------------------------------------------------------------------------
// Enumeración para indicar el origen del comando recibido
// ---------------------------------------------------------------------------
enum CommandSource {
    SOURCE_NONE = 0,           // Ningún comando ha sido recibido aún
    SOURCE_BUTTON = 1,         // Comando generado por botón físico
    SOURCE_SERIAL_LOCAL = 2,   // Comando recibido por Serial (USB)
    SOURCE_SERIAL_MASTER = 3   // Comando recibido por SerialNodeMaster
};


// ---------------------------------------------------------------------------
// Inicializa el parser (si se requiere configuración adicional futura)
// (Nota: En esta versión, el parser no requiere setup explícito)
// ---------------------------------------------------------------------------
// void initCommandParser();  // (no necesario actualmente)


// ---------------------------------------------------------------------------
// Funciones de detección de comandos desde diferentes fuentes
// Estas funciones deben llamarse periódicamente desde el `loop()` principal
// ---------------------------------------------------------------------------
bool checkLineFromLocal();       // Analiza entrada desde Serial (USB)
bool checkLineFromMaster();      // Analiza entrada desde SerialNodeMaster
void setCommandFromButton(char cmd, int val);  // Carga comando manual desde botón


// ---------------------------------------------------------------------------
// Getters para acceder al comando procesado
// ---------------------------------------------------------------------------
char getParsedCommand();         // Retorna el carácter del comando (ej. 'G')
int getParsedValue();            // Retorna el valor numérico del comando (ej. 1)
CommandSource getParsedSource(); // Retorna el origen del comando

// ---------------------------------------------------------------------------
// Limpia las variables internas para aceptar un nuevo comando
// ---------------------------------------------------------------------------
void clearParsedCommand();

#endif  // COMMAND_PARSER_H
