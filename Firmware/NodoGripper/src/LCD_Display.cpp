#include <Arduino.h>
#include "LCD_Display.h"
#include "Hardware_GripperNode.h"

// Configura la pantalla con los pines definidos
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void initLCD() {
    lcd.begin(16, 2);  // LCD 16x2
    lcd.clear();
    lcd.print("Gripper Node");
    lcd.setCursor(0, 1);
    lcd.print("LCD ready...");
    delay(1000);
    lcd.clear();

    pinMode(BUZZER, OUTPUT);
    digitalWrite(BUZZER, LOW);
}

void beep() {
    digitalWrite(BUZZER, HIGH);
    delay(80);
    digitalWrite(BUZZER, LOW);
}

void beepError() {
    // Beep doble para indicar error
    for (int i = 0; i < 2; i++) {
        digitalWrite(BUZZER, HIGH);
        delay(100);
        digitalWrite(BUZZER, LOW);
        delay(100);
    }
}
