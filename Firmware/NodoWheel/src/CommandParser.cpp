#include <Arduino.h>
#include "Hardware_NodeWheel.h"

static String input = "";
static char parsedCommand = 0;
static int parsedValue = 0;

bool checkLineFromMaster() {
    while (SerialNodeMaster.available() > 0) {
        char c = SerialNodeMaster.read();
        if (c == '\r') {
            if (input.length() > 0) {
                parsedCommand = input.charAt(0);
                parsedValue = input.substring(1).toInt();
                input = "";
                return true;
            }
        } else if (c != '\n') {
            input += c;
        }
    }
    return false;
}

char getParsedCommand() {
    return parsedCommand;
}

int getParsedValue() {
    return parsedValue;
}
