#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal.h>

// Inicializa la pantalla LCD
void initLCD();

// Función para emitir un beep simple
void beep();

// Función para emitir un beep de error (más largo o doble)
void beepError();

// Objeto global de pantalla LCD (4-bit mode)
extern LiquidCrystal lcd;

#endif
