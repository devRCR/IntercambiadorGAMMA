/*******************************************************************************************
 * Proyecto: Control Distribuido - Nodo Esclavo Spindle
 * Archivo:  main.cpp / sketch_GAMMA_NodeSlave_Spindle.ino
 * Autores:  O. Baltuano, R. Chan
 * Laboratorio de Desarrollo Electrónico
 * INSTITUTO PERUANO DE ENERGÍA NUCLEAR (IPEN)
 *
 * Descripción:
 * Este módulo controla el accionamiento del husillo (Spindle) del intercambiador Gamma,
 * recibiendo comandos seriales y ejecutando acciones motrices correspondientes.
 *
 * Licencia:
 * Este código se distribuye bajo los términos de la licencia Creative Commons
 * Atribución-NoComercial 4.0 Internacional (CC BY-NC 4.0).
 *
 * - Permitido: uso, copia y modificación con fines no comerciales, indicando autores.
 * - Prohibido: uso o redistribución con fines comerciales sin autorización expresa.
 * - Si se modifica este archivo, se debe declarar el autor del cambio.
 *
 * Más información: https://creativecommons.org/licenses/by-nc/4.0/
 *******************************************************************************************/

#include <Arduino.h>
#include <LiquidCrystal.h>
//#include <SoftwareSerial.h>
#include "Hardware_NodeSlave.h"


int us_delay = 1000;

boolean FLAG_RUNNING_MANUAL;
boolean DIRECTION;
boolean GO_FULL_RIGHT;
int PosActual = 0;

//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Configura software serial para sensor ultrasónico
//SoftwareSerial mySerial(13,8); // RX, TX
unsigned char data[4]={};
float distance;

// Variables de temporización
unsigned long MillisPrevio = 0;
unsigned long MillisActual = 0;

unsigned long MillisTestPrevio = 0;
unsigned long MillisTestActual = 0;

unsigned int RUNNING_MODE = FLAG_STOP;
unsigned int SERIAL_ACTION = SERIAL_STOP;

// Decodificación de trama recibida desde la PC
char RxChar = 0;
String RxString = "";
char command = 0;
int value = 0;

// Decodificación de trama recibida desde puerto Serial 1 Node Master
char RxChar_NodeMaster = 0;
String RxString_NodeMaster = "";
char command_NodeMaster = 0;
int value_NodeMaster = 0;

// ==== Prototipos de funciones ====
bool Check_Line_Rx();
void Exec_Command_Rx();
bool Check_Line_Rx_NodeMaster();
void Exec_Command_Rx_NodeMaster();
void SoundBeepAtention();
void SoundBeepError();
void MoveOneStep();


//====================================================================
//  S E T U P 
//====================================================================
void setup() {
  Serial.begin(115200);

  SerialNodeMaster.begin(9600);
  
//  pinMode(RS485_RE,OUTPUT);
//  digitalWrite(RS485_RE,LOW);
//  pinMode(RS485_DE,OUTPUT);
//  digitalWrite(RS485_RE,LOW);  
  
//  mySerial.begin(9600);

  //GO_FULL_RIGHT = false;
  FLAG_RUNNING_MANUAL = false;  
  
  // MOTOR HUSILLO
  pinMode(M_EN,OUTPUT);
  digitalWrite(M_EN,HIGH);
  pinMode(M_STEP,OUTPUT);
  digitalWrite(M_STEP,HIGH);  
  pinMode(M_DIR,OUTPUT);
  DIRECTION = DirLeft;
  digitalWrite(M_DIR,DIRECTION);  
  
  
  // PANEL LCD
  pinMode(LCD_RW,OUTPUT);
  digitalWrite(LCD_RW,LOW);
  lcd.begin(16, 2);
  lcd.print("Hello...");

  // RELAY
  pinMode(RELAY,OUTPUT);
  digitalWrite(RELAY,LOW);  

  // BUZZER
  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,LOW); 

  // ANILLO INFERIOR DE SENSORES
  pinMode(SENS_RING01,INPUT);
  pinMode(SENS_RING02,INPUT);
  pinMode(SENS_RING03,INPUT);

  // SENSORES DETECTOR MARINELLI GARRA
  pinMode(SENS_MAR1,INPUT);
  pinMode(SENS_MAR2,INPUT);
  pinMode(SENS_MAR3,INPUT);    

  // SENSORES MAGNETICOS GARRA
  pinMode(SENS_CLAW_OPEN,INPUT);
  pinMode(SENS_CLAW_CLOSE,INPUT);

  // SENSORES DEL HUSILLO
  pinMode(SENS_POS1,INPUT_PULLUP);
  pinMode(SENS_POS2,INPUT_PULLUP);  
  pinMode(SENS_POS2,INPUT_PULLUP);

  // BOTONES MOVIMIENTO DEL HUSILLO
  pinMode(BTN_GO_POS1,INPUT);
  pinMode(BTN_GO_POS2,INPUT);
  pinMode(BTN_GO_POS3,INPUT);
  pinMode(BTN_STOP,   INPUT);

  pinMode(BTN_MARI_CATCH_TOP,INPUT);
  pinMode(BTN_MARI_RELEASE_TOP,INPUT);  
  pinMode(BTN_MARI_CATCH_BOTTOM,INPUT);  
  pinMode(BTN_MARI_RELEASE_BOTTOM,INPUT);

  pinMode(BTN_GENERAL1,INPUT);
  pinMode(BTN_GENERAL2,INPUT);  
  pinMode(BTN_GENERAL3,INPUT);  
  pinMode(BTN_GENERAL4,INPUT);

  pinMode(JUMPER1,INPUT);
  pinMode(JUMPER2,INPUT);
  pinMode(JUMPER3,INPUT);
  pinMode(JUMPER4,INPUT);
}

//====================================================================
//  M A I N   L O O P
//====================================================================
void loop() {

    if (Check_Line_Rx()) Exec_Command_Rx();
    if (Check_Line_Rx_NodeMaster()) Exec_Command_Rx_NodeMaster();
  
    // ---- BOTON DE EMERGENCIA --------------------------------------
    // ---- Detiene cualquier proceso en marcha ----------------------
    if ((!digitalRead(BTN_STOP))or(SERIAL_ACTION==SERIAL_STOP)) {
          SERIAL_ACTION = SERIAL_NONE;
          RUNNING_MODE = FLAG_STOP;
          digitalWrite(M_EN,HIGH);
          lcd.clear();
          lcd.print("STOP MANUAL");
          SoundBeepAtention();          
          
    }
    // ---- BOTONES MANUALES ----------------------------------------
    // ---- Sólo operan los botones si se encuentra en modo FLAG-STOP
    if (RUNNING_MODE == FLAG_STOP) {
          //------------------------------------------
          if ((!digitalRead(BTN_GO_POS1))or(SERIAL_ACTION==SERIAL_GO_POS_01)) {
                SERIAL_ACTION = SERIAL_NONE;
                if (!digitalRead(SENS_POS1)) {
                        RUNNING_MODE = FLAG_GO_POS_01;
                        }
                   else {
                        lcd.clear();
                        lcd.print("< POS 01 >");
                        SoundBeepAtention();
                        }
              }
          //------------------------------------------
          if ((!digitalRead(BTN_GO_POS2))or(SERIAL_ACTION==SERIAL_GO_POS_02)) {
                SERIAL_ACTION = SERIAL_NONE;
                if (!digitalRead(SENS_POS2)) {
                        if (digitalRead(SENS_POS1)) {
                                  RUNNING_MODE = FLAG_GO_POS_02;
                                  }
                            else {
                                 lcd.clear();
                                 lcd.print("Error position");
                                 lcd.setCursor(0, 1);
                                 lcd.print("Need user inter.");
                                 SoundBeepError();
                                 }
                        }
                   else {
                        lcd.clear();
                        lcd.print(" < In POS 02 >");
                        SoundBeepAtention();
                        }
              }
          //------------------------------------------
          if ((!digitalRead(BTN_GO_POS3))or(SERIAL_ACTION==SERIAL_GO_POS_03)) {
                SERIAL_ACTION = SERIAL_NONE;
                if (digitalRead(SENS_POS1)) {
                          RUNNING_MODE = FLAG_GO_POS_03;
                          }
                    else {
                         lcd.clear();
                         lcd.print("Error position");
                         lcd.setCursor(0, 1);
                         lcd.print("Need user inter.");
                         SoundBeepError();
                         }
              }
          //------------------------------------------
          if (!digitalRead(BTN_MARI_CATCH_BOTTOM)) {
                if (digitalRead(SENS_POS1)) {
                     RUNNING_MODE = FLAG_MARI_CATCH_BOTTOM;
                     }
                else {
                     lcd.clear();
                     lcd.print("Unable Catch Mar");
                     lcd.setCursor(0, 1);
                     lcd.print("Wrong position 2");               
                     SoundBeepError();            
                     }   
              }
          //------------------------------------------
          if (!digitalRead(BTN_MARI_CATCH_TOP)) {
                if (digitalRead(SENS_POS2)) {
                     RUNNING_MODE = FLAG_MARI_CATCH_TOP;
                     }
                else {
                     lcd.clear();
                     lcd.print("Unable Catch Mar");
                     lcd.setCursor(0, 1);
                     lcd.print("Wrong position 2");               
                     SoundBeepError();            
                     }   
              }
          //------------------------------------------              
          if (!digitalRead(BTN_MARI_RELEASE_TOP)) {
                if (digitalRead(SENS_POS2)) {
                     RUNNING_MODE = FLAG_MARI_RELEASE_TOP;
                     }
                else {
                     lcd.clear();
                     lcd.print("Unable Release");
                     lcd.setCursor(0, 1);
                     lcd.print("Must be in POS 2");               
                     SoundBeepError();            
                     }   
              }
    }
    
    switch (RUNNING_MODE) {
            case FLAG_GO_POS_01:    
                                  if (!digitalRead(SENS_POS1)) {
                                          MillisActual = millis();
                                          DIRECTION = DirLeft;
                                          digitalWrite(M_EN,LOW);
                                          MoveOneStep();
                                          }
                                     else {
                                          RUNNING_MODE = FLAG_STOP;
                                          digitalWrite(M_EN,HIGH);
                                          lcd.clear();
                                          lcd.print("POS 01 ...");
                                          SoundBeepAtention();
                                          }
                                  break;
            case FLAG_GO_POS_02:
                                  if (!digitalRead(SENS_POS2)) {
                                          MillisActual = millis();
                                          DIRECTION = DirRight;
                                          digitalWrite(M_EN,LOW);
                                          MoveOneStep();
                                          }
                                     else {
                                          RUNNING_MODE = FLAG_STOP;
                                          digitalWrite(M_EN,HIGH);
                                          lcd.clear();
                                          lcd.print(" < In POS 02 >");
                                          SoundBeepAtention();
                                          }
                                  break;
            case FLAG_GO_POS_03:
                                  if ((!digitalRead(SENS_RING01)) and
                                      (!digitalRead(SENS_RING02)) and
                                      (!digitalRead(SENS_RING03))) {
                                          DIRECTION = DirRight;
                                          digitalWrite(M_EN,LOW);
                                          MoveOneStep();
                                          }
                                     else {
                                          RUNNING_MODE = FLAG_STOP;
                                          digitalWrite(M_EN,HIGH);
                                          lcd.clear();
                                          lcd.print(" < Marinelli over >");
                                          lcd.setCursor(0, 1);
                                          lcd.print("detector");  
                                          SoundBeepAtention();
                                          }
                                  break;
            case FLAG_MARI_CATCH_BOTTOM:
                                  if ((digitalRead(SENS_MAR1)) and
                                      (digitalRead(SENS_MAR2)) and
                                      (digitalRead(SENS_MAR3))) {
                                            RUNNING_MODE = FLAG_STOP;
                                            digitalWrite(M_EN,HIGH);
                                            SoundBeepAtention(); 
                                            digitalWrite(RELAY,HIGH);
                                            lcd.clear();
                                            lcd.print("CATCH MARIN");   
                                            }
                                       else {
                                            MillisActual = millis();
                                            DIRECTION = DirRight;
                                            digitalWrite(M_EN,LOW);
                                            MoveOneStep();
                                       }
                                  break;                                  
            case FLAG_MARI_CATCH_TOP:
                                  if ((digitalRead(SENS_MAR1)) and
                                      (digitalRead(SENS_MAR2)) and
                                      (digitalRead(SENS_MAR3))) {
                                            RUNNING_MODE = FLAG_STOP;
                                            digitalWrite(M_EN,HIGH);
                                            SoundBeepAtention(); 
                                            digitalWrite(RELAY,HIGH);
                                            lcd.clear();
                                            lcd.print("CATCH MARIN");   
                                            }
                                       else {
                                            MillisActual = millis();
                                            DIRECTION = DirRight;
                                            digitalWrite(M_EN,LOW);
                                            MoveOneStep();
                                       }
                                  break;                                     
            case FLAG_MARI_RELEASE_TOP:
                                  digitalWrite(RELAY,LOW);
                                  delay(200);
                                  if ((digitalRead(SENS_MAR1)) or
                                      (digitalRead(SENS_MAR2)) or
                                      (digitalRead(SENS_MAR3))) {
                                            lcd.clear();
                                            digitalWrite(BUZZER,HIGH);
                                            delay(500);
                                            digitalWrite(BUZZER,LOW);
                                            lcd.print(" << ERROR >> ");
                                            lcd.setCursor(0, 1);
                                            lcd.print("Falling marinelli");
                                            delay(300);    
                                            }
                                       else {
                                            RUNNING_MODE = FLAG_STOP;
                                            lcd.clear();
                                            lcd.print("Marineli release");
                                            lcd.setCursor(0, 1);
                                            lcd.print("over in position");  
                                            SoundBeepAtention();
                                       }
                                  break;
            default:
                                  RUNNING_MODE = RUNNING_MODE;
    }

    if (!digitalRead(BTN_GENERAL3))  digitalWrite(RELAY,LOW);
    if (!digitalRead(BTN_GENERAL4)) digitalWrite(RELAY,HIGH);
    
    if (!digitalRead(BTN_GENERAL1)) {
                FLAG_RUNNING_MANUAL = true;
                MillisActual = millis();
                DIRECTION = DirLeft;
                digitalWrite(M_EN,LOW);
                MoveOneStep();
                }
                
    if (!digitalRead(BTN_GENERAL2)) {
                if ((digitalRead(SENS_RING01)) or
                    (digitalRead(SENS_RING02)) or
                    (digitalRead(SENS_RING03))) {
                          digitalWrite(BUZZER,HIGH);
                          delay(500);
                          digitalWrite(BUZZER,LOW);
                          }
                DIRECTION = DirRight;
                digitalWrite(M_EN,LOW);
                MoveOneStep();
                }

              
    if (FLAG_RUNNING_MANUAL) 
                if (MillisActual - MillisPrevio < 100) {
                    MillisPrevio = MillisActual;
                }
                else { 
                    FLAG_RUNNING_MANUAL = false;
                    digitalWrite(M_EN,HIGH);
                }

    if (digitalRead(JUMPER1)) {
        MillisTestActual = millis();
        if (MillisTestActual-MillisTestPrevio>= 250) {
                MillisTestPrevio = MillisTestActual;
                lcd.setCursor(0,0);
                if (digitalRead(SENS_POS1)) {
                                lcd.print("POS 01 ...");
                                digitalWrite(BUZZER,HIGH);
                                delay(250);
                                digitalWrite(BUZZER,LOW);
                                }
                if (digitalRead(SENS_POS2)) {
                                lcd.print("POS 02 ...");
                                digitalWrite(BUZZER,HIGH);
                                delay(250);
                                digitalWrite(BUZZER,LOW);
                                }
                if (digitalRead(SENS_POS3)) {
                                lcd.print("POS 03 ...");
                                digitalWrite(BUZZER,HIGH);
                                delay(250);
                                digitalWrite(BUZZER,LOW);
                                }
                }  
    }
}

void SoundBeepError() {
    digitalWrite(BUZZER,HIGH);
    delay(1500);
    digitalWrite(BUZZER,LOW);
}

void SoundBeepAtention() {
    digitalWrite(BUZZER,HIGH);
    delay(250);
    digitalWrite(BUZZER,LOW);
}

// Gira el motor un paso en función a la dirección
// que ha sido configurada en la variable DIRECTION
void MoveOneStep() {
    digitalWrite(M_DIR,DIRECTION);    // Configura la dirección 
    digitalWrite(M_STEP,LOW);         // 
    delayMicroseconds(500);                       // Pulso bajo de 100 us
    digitalWrite(M_STEP,HIGH);        //
    delayMicroseconds(us_delay);                // Retardo movimiento motor
    if (!GO_FULL_RIGHT) {
        if (DIRECTION) PosActual++;
                  else PosActual--;
        if ((PosActual % 5) == 0 ) {
              //Serial.print('p');
              //Serial.print(PosActual);
              //Serial.print(" | ");
              //Serial.println(Value_Speed);
              us_delay = 1000 + 3 * analogRead(SENS_SPEED);               
              }
        }
}

// ------------------------------------------------
// Convierte un String de entrada en valor entero
//-------------------------------------------------
int StringToInt(String cadena) {
    char tmp_array[cadena.length()+1];
    cadena.toCharArray(tmp_array,sizeof(tmp_array));
    return atoi(tmp_array);
}

// ------------------------------------------------
// Ejecuta el comando recibido
//-------------------------------------------------
void Exec_Command_Rx() {
    switch (command) {
            case 'T' : SERIAL_ACTION = SERIAL_STOP;
                       break;
            case 'G' : if (value==1) SERIAL_ACTION = SERIAL_GO_POS_01;
                       if (value==2) SERIAL_ACTION = SERIAL_GO_POS_02;
                       break;
            case '?' :
                       Serial.println("GAMMA01-H02C210207");
                       break;
            default  : 
                       Serial.println("Comando no reconocido");
    }
}

void Exec_Command_Rx_NodeMaster() {
    switch (command_NodeMaster) {
            case 'T' : SERIAL_ACTION = SERIAL_STOP;
                       break;
            case 'G' : if (value_NodeMaster==1) SERIAL_ACTION = SERIAL_GO_POS_01;
                       if (value_NodeMaster==2) SERIAL_ACTION = SERIAL_GO_POS_02;
                       //if (value_NodeMaster==3) SERIAL_ACTION = SERIAL_GO_POS_03;
                       break;
            case '?' :
                       Serial.println("GAMMA01-H02C210207");
                       break;
            default  : 
                       Serial.println("Comando no reconocido");
    }  
}

// ------------------------------------------------------------------------
// Check si se ha recibido "Enter" (13) -> extrae comando y valor
// El comando es el primer caracter (0) de la linea recibida en tipo "char"
// El valor es el segundo caracter (1) en adelante en tipo "int"
//-------------------------------------------------------------------------
boolean Check_Line_Rx() {
    if ( Serial.available() > 0 ) {
        RxChar = Serial.read();
        if ( RxChar > 0 )
            switch (RxChar) {
                    case 13 : if (RxString.length()==0) return false;
                              command = RxString.charAt(0);
                              value = StringToInt(RxString.substring(1));
                              RxString = "";
                              return true;
                              break;
                    case 10 : break;
                    default : RxString += RxChar;
            }    
    }
    return false;
}

// ------------------------------------------------------------------------
// Check si se ha recibido "Enter" (13) -> extrae comando y valor
// El comando es el primer caracter (0) de la linea recibida en tipo "char"
// El valor es el segundo caracter (1) en adelante en tipo "int"
//-------------------------------------------------------------------------
boolean Check_Line_Rx_NodeMaster() {
    if ( SerialNodeMaster.available() > 0 ) {
        RxChar_NodeMaster = SerialNodeMaster.read();
        if ( RxChar_NodeMaster > 0 )
            switch (RxChar_NodeMaster) {
                    case 13 : if (RxString_NodeMaster.length()==0) return false;
                              command_NodeMaster = RxString_NodeMaster.charAt(0);
                              value_NodeMaster = StringToInt(RxString_NodeMaster.substring(1));
                              RxString_NodeMaster = "";
                              return true;
                              break;
                    case 10 : break;
                    default : RxString_NodeMaster += RxChar_NodeMaster;
            }    
    }
    return false;
}

  