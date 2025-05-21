#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

// Fuente del comando recibido
enum CommandSource {
    SOURCE_NONE = 0,
    SOURCE_BUTTON = 1,
    SOURCE_SERIAL_LOCAL = 2,
    SOURCE_SERIAL_MASTER = 3
};

// Funciones de parser
bool checkLineFromLocal();
bool checkLineFromMaster();
void setCommandFromButton(char cmd, int val);

char getParsedCommand();
int getParsedValue();
CommandSource getParsedSource();

void clearParsedCommand(); // Reinicia comando

#endif
