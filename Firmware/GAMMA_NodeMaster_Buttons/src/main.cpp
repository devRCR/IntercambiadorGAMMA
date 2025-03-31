#include <Arduino.h>
#include "Hardware_NodeMaster.h"

// Decodificación de trama recibida desde puerto Serial
char RxChar = 0;
String RxString = "";
char command = 0;
int value = 0;

// Decodificación de trama recibida desde puerto Serial1 (485)
char RxChar_RS485 = 0;
String RxString_RS485 = "";
char command_RS485 = 0;
int value_RS485 = 0;

// Decodificación de trama recibida desde puerto Serial2
char    RxChar_Serial2    = 0;
String  RxString_Serial2  = "";
char    command_Serial2   = 0;
int     value_Serial2     = 0;

// Variables internas
int     MODE_AUTO = 0;  
boolean FLAG_NEXT = false; 

// Prototipos de Funciones Faltantes
bool Check_Line_Rx();
void Exec_Command_Rx();
bool Check_Line_Rx_RS485();
void Exec_Command_Rx_RS485();


void setup() {
  pinMode(BTN_SAMPLE_NEXT,  INPUT_PULLUP);
  pinMode(BTN_SAMPLE_CYCLE, INPUT_PULLUP);  
  pinMode(BTN_PLATE_DOWN,   INPUT_PULLUP);
  pinMode(BTN_PLATE_UP,     INPUT_PULLUP);
  pinMode(BTN_SHIELD_OPEN,  INPUT_PULLUP);  
  pinMode(BTN_SHIELD_CLOSE, INPUT_PULLUP);

  pinMode(BTN_STOP,             INPUT_PULLUP);
  pinMode(BTN_GO_POS_1,         INPUT_PULLUP);
  pinMode(BTN_GO_POS_2,         INPUT_PULLUP);
  pinMode(BTN_MARI_CATCH_TOP,   INPUT_PULLUP);
  pinMode(BTN_MARI_RELEASE_TOP, INPUT_PULLUP);
  


  Serial.begin(115200);
  SerialNodeWheel.begin(9600);
  SerialNodeSpindle.begin(9600);  
  delay(500);
}

void loop() {
    // Escucha comandos del puerto serial
    if (Check_Line_Rx()) Exec_Command_Rx();
    if (Check_Line_Rx_RS485()) Exec_Command_Rx_RS485();
    
    if (!digitalRead(BTN_SAMPLE_NEXT)) {
          SerialNodeWheel.println(CMD_SAMPLE_NEXT);
          delay(200);
          }
    if (!digitalRead(BTN_SAMPLE_CYCLE)) {
          SerialNodeWheel.println(CMD_SAMPLE_CYCLE);
          delay(200);
          }
    if (!digitalRead(BTN_PLATE_DOWN)) {
          SerialNodeWheel.println(CMD_PLATE_DOWN);
          delay(200);
          }
    if (!digitalRead(BTN_PLATE_UP)) {
          SerialNodeWheel.println(CMD_PLATE_UP);
          delay(200);
          }
    if (!digitalRead(BTN_SHIELD_OPEN)) {
          SerialNodeWheel.println(CMD_SHIELD_OPEN);
          delay(200);
          }
    if (!digitalRead(BTN_SHIELD_CLOSE)) {
          SerialNodeWheel.println(CMD_SHIELD_CLOSE);
          delay(200);
          }

    if (!digitalRead(BTN_STOP)) {
          SerialNodeSpindle.println(CMD_STOP);
          delay(200);
          }
    if (!digitalRead(BTN_GO_POS_1)) {
          SerialNodeSpindle.println(CMD_GO_POS_1);
          delay(200);
          }
    if (!digitalRead(BTN_GO_POS_2)) {
          SerialNodeSpindle.println(CMD_GO_POS_2);
          delay(200);
          }

    if (!digitalRead(BTN_SECUENCE)) {
          MODE_AUTO = STATE_SHIELD_CLOSE;
          FLAG_NEXT = true;
          delay(200);
          }

    if (FLAG_NEXT) {
        FLAG_NEXT = false;
        switch (MODE_AUTO) {
              case STATE_SHIELD_CLOSE : 
                                delay(1000);
                                SerialNodeWheel.println(CMD_SHIELD_CLOSE);
                                break;
              case STATE_PLATE_UP : 
                                delay(1000);
                                SerialNodeWheel.println(CMD_PLATE_UP);
                                break;
              case STATE_SHIELD_OPEN : 
                                delay(1000);
                                SerialNodeWheel.println(CMD_SHIELD_OPEN);
                                break;
              case STATE_PLATE_DOWN : 
                                delay(1000);
                                SerialNodeWheel.println(CMD_PLATE_DOWN);
                                break;
              case STATE_SAMPLE_NEXT : 
                                delay(1000);
                                SerialNodeWheel.println(CMD_SAMPLE_NEXT);
                                break;
              default :
                                MODE_AUTO = 0;
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
// Ejecuta el comando recibido desde el puerto Serial
//-------------------------------------------------
void Exec_Command_Rx() {
    switch (command) {
            case 's' : 
                       break;
            case 'g' : 
                       break;
            case '?' :
                       Serial.println("GAMMA01-H02C210207");
                       break;
            default  : 
                       Serial.println("Comando no reconocido");
    }
}

// ------------------------------------------------
// Ejecuta el comando recibido desde el puerto Serial1 (RS485)
//-------------------------------------------------
void Exec_Command_Rx_RS485() {
    switch (command_RS485) {
            case 'K' : if ((MODE_AUTO==STATE_SHIELD_CLOSE)and(value_RS485==STATE_SHIELD_CLOSE)) {
                            MODE_AUTO = STATE_PLATE_UP;
                            FLAG_NEXT = true;
                            }
                       if ((MODE_AUTO==STATE_PLATE_UP)and(value_RS485==STATE_PLATE_UP)) {
                            MODE_AUTO = STATE_SAMPLE_NEXT;
                            FLAG_NEXT = true;
                            }                            
                       break;
            case 'E' : 
                       MODE_AUTO = 0;
                       FLAG_NEXT = false;
                       break;
            default  : 
                       value_RS485 = 0;     // No tiene importancia
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
        //Serial1.print(RxChar);
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
boolean Check_Line_Rx_RS485() {
    if ( Serial1.available() > 0 ) {
        RxChar_RS485 = Serial1.read();
        Serial.print(RxChar_RS485);
        if ( RxChar_RS485 > 0 )
            switch (RxChar_RS485) {
                    case 13 : if (RxString_RS485.length()==0) return false;
                              command_RS485 = RxString_RS485.charAt(0);
                              value_RS485 = StringToInt(RxString_RS485.substring(1));
                              RxString_RS485 = "";
                              return true;
                              break;
                    case 10 : break;
                    default : RxString_RS485 += RxChar_RS485;
            }    
    }
    return false;
}