// Version 1.5 - 01 julio 2024
//    Se modifico para recibir comandos desde el nodo teclado
//    Se quitaron los controles de los pulsadores locales

#include "Hardware_NodeSlave_Wheel.h"

int RUNNING = 0;
unsigned int SERIAL_ACTION = SERIAL_STOP;

boolean DEBUG = true;

// Decodificación de trama recibida desde puerto Serial 1 (485)
char RxChar_RS485 = 0;
String RxString_RS485 = "";
char command_RS485 = 0;
int value_RS485 = 0;

void setup() {
  Serial1.begin(9600);
  
  // put your setup code here, to run once:
  if (DEBUG) Serial.begin(115200);
  delay(1000);
  
  pinMode(BUZZER,OUTPUT);
  digitalWrite(BUZZER,HIGH);
  delay(250);
  digitalWrite(BUZZER,LOW);
  if (DEBUG) Serial.println("Iniciando...");

  // --- CONTROL DE LA MESA NIVELADORA ---
  pinMode(SENSOR_TOP1,INPUT_PULLUP);
  pinMode(SENSOR_TOP2,INPUT_PULLUP);
  pinMode(SENSOR_BOTTOM1,INPUT_PULLUP);
  pinMode(SENSOR_BOTTOM2,INPUT_PULLUP);
  pinMode(BTN_UP,  INPUT_PULLUP);
  pinMode(BTN_DOWN,INPUT_PULLUP);  
  pinMode(MOTOR_PWM,OUTPUT);
  analogWrite(MOTOR_PWM,SPEED_HIGH);
  pinMode(DRIVER_IN1,OUTPUT);
  pinMode(DRIVER_IN2,OUTPUT);  
  digitalWrite(DRIVER_IN1,LOW);
  digitalWrite(DRIVER_IN2,LOW);  

  pinMode(SENS_BLUE,  INPUT);
  pinMode(SENS_GREEN, INPUT);
  pinMode(SENS_VIOLET,INPUT);
  pinMode(SENS_ORANGE,INPUT);
  
  pinMode(BTN_CYCLE, INPUT);
  pinMode(BTN_NEXT, INPUT);
  pinMode(BTN_OPEN,INPUT);
  pinMode(BTN_CLOSE,INPUT);
    
  pinMode(RLY_DOOR_OPEN,OUTPUT);
  digitalWrite(RLY_DOOR_OPEN,HIGH);
  pinMode(RLY_DOOR_CLOSE,OUTPUT);
  digitalWrite(RLY_DOOR_CLOSE,HIGH);
  pinMode(RLY_SAMPLE_NEXT,OUTPUT);
  digitalWrite(RLY_SAMPLE_NEXT,HIGH);
  pinMode(RLY_B2_R04,OUTPUT);
  digitalWrite(RLY_B2_R04,HIGH);
  pinMode(RLY_B2_R05,OUTPUT);
  digitalWrite(RLY_B2_R05,HIGH);
  pinMode(RLY_B2_R06,OUTPUT);
  digitalWrite(RLY_B2_R06,HIGH);
  pinMode(RLY_B2_R07,OUTPUT);
  digitalWrite(RLY_B2_R07,HIGH);
  pinMode(RLY_B2_R08,OUTPUT);
  digitalWrite(RLY_B2_R08,HIGH);
}

void loop() {
//----------------------------------------------------
// VERIFICA SI HAY DATOS EN EL PUERTOS SERIAL-RS485
    if (Check_Line_Rx_RS485()) Exec_Command_Rx_RS485();

//----------------------------------------------------
// CAMBIO DE MUESTRA
    if ((!digitalRead(BTN_NEXT))or(SERIAL_ACTION==SERIAL_SAMPLE_NEXT)) {
        SERIAL_ACTION = SERIAL_NONE;
        if (digitalRead(SENSOR_TOP1) or digitalRead(SENSOR_TOP2)){
            digitalWrite(RLY_SAMPLE_NEXT,LOW);
            delay(1000);
            while (!digitalRead(SENS_ORANGE));
            digitalWrite(RLY_SAMPLE_NEXT,HIGH);
            digitalWrite(BUZZER,HIGH);
            delay(250);
            digitalWrite(BUZZER,LOW); 
            if (DEBUG) Serial.println("NEXT completado"); 
            delay(1000);                
            }
        }

//----------------------------------------------------
// ABRIR TAPA BLINDAJE (D11)
    if ((!digitalRead(BTN_OPEN))or(SERIAL_ACTION==SERIAL_DOOR_OPEN)) {
        SERIAL_ACTION = SERIAL_NONE;
        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
              // Sólo se abre la tapa si los dos sensores del plato
              // elevador se encuentran activados en la parte inferior
                {
                digitalWrite(RLY_DOOR_OPEN,LOW);
                while (!digitalRead(SENS_GREEN));
                digitalWrite(RLY_DOOR_OPEN,HIGH); 
                if (DEBUG) Serial.println("ALERTA: Tapa de blindaje totalment abierta");
                }
           else {
                digitalWrite(BUZZER,HIGH);
                delay(1000);
                digitalWrite(BUZZER,LOW);
                if (DEBUG) Serial.println("ERROR: Mesa niveladora no se encuentra en posicion inferior");
                }
    }

//----------------------------------------------------
// CERRAR TAPA BLINDAJE (D12)
    if ((!digitalRead(BTN_CLOSE))or(SERIAL_ACTION==SERIAL_DOOR_CLOSE)) {
        SERIAL_ACTION = SERIAL_NONE;
        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
              // Sólo se cierra la tapa si los dos sensores del plato
              // elevador se encuentran activados en la parte inferior
                {
                digitalWrite(RLY_DOOR_CLOSE,LOW);
                while (!digitalRead(SENS_BLUE));
                digitalWrite(RLY_DOOR_CLOSE,HIGH);
                if (DEBUG) Serial.println("ALERTA: Tapa de blindaje totalment cerrada");       
                }
           else {
                digitalWrite(BUZZER,HIGH);
                delay(1000);
                digitalWrite(BUZZER,LOW);
                if (DEBUG) Serial.println("ERROR: Mesa niveladora NO se encuentra en posicin inferior");
                }
    }    

//----------------------------------------------------
// BAJAR MESA NIVELADORA (D6)
    if ((!digitalRead(BTN_DOWN))or(SERIAL_ACTION==SERIAL_TABLE_DOWN)) {
          SERIAL_ACTION = SERIAL_NONE;
          if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) {
                for (int i=1; i<=3; i++) {
                      digitalWrite(BUZZER,HIGH);
                      delay(200);
                      digitalWrite(BUZZER,LOW);
                      delay(200);
                      }
                if (DEBUG) Serial.println("ALERTA: Mesa niveladora YA en encuentra en posición inferior");
                }
          else {
                digitalWrite(DRIVER_IN1,HIGH);
                digitalWrite(DRIVER_IN2,LOW);
                analogWrite(MOTOR_PWM,SPEED_HIGH);
                RUNNING = 1;
                }
    }
    
//----------------------------------------------------
// SUBIR MESA NIVELADORA (D5)
    if ((!digitalRead(BTN_UP))or(SERIAL_ACTION==SERIAL_TABLE_UP)) {
          SERIAL_ACTION = SERIAL_NONE;
          if (digitalRead(SENS_BLUE)) {
                 if (digitalRead(SENSOR_TOP1)&&digitalRead(SENSOR_TOP2)) {
                              for (int i=1; i<=3; i++) {
                                    digitalWrite(BUZZER,HIGH);
                                    delay(200);
                                    digitalWrite(BUZZER,LOW);
                                    delay(200);
                                    }
                              if (DEBUG) Serial.println("ALERTA: Mesa niveladora YA en encuentra en posición superior");
                              }
                        else  {
                              digitalWrite(DRIVER_IN1,LOW);
                              digitalWrite(DRIVER_IN2,HIGH);
                              analogWrite(MOTOR_PWM,SPEED_HIGH);
                              RUNNING = 2;
                              }
                         }
            else {
                 digitalWrite(BUZZER,HIGH);
                 delay(1000);
                 digitalWrite(BUZZER,LOW);          
                 }
          }
    
  if (RUNNING==1) {
          if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) {
                digitalWrite(DRIVER_IN1,LOW);
                digitalWrite(DRIVER_IN2,LOW);
                RUNNING = 0; 
                analogWrite(MOTOR_PWM,SPEED_HIGH); 
                digitalWrite(BUZZER,HIGH);
                delay(250);
                digitalWrite(BUZZER,LOW);
                if (DEBUG) Serial.println("ALERTA: Mesa niveladora LLEGO a posición inferior");
                }
          if (digitalRead(SENSOR_BOTTOM1)||digitalRead(SENSOR_BOTTOM2)) {
                analogWrite(MOTOR_PWM,SPEED_LOW);
                }
          }
  if (RUNNING==2) {
          if (digitalRead(SENSOR_TOP1)&&digitalRead(SENSOR_TOP2)) {
                digitalWrite(DRIVER_IN1,LOW);
                digitalWrite(DRIVER_IN2,LOW);
                RUNNING = 0; 
                analogWrite(MOTOR_PWM,SPEED_HIGH); 
                digitalWrite(BUZZER,HIGH);
                delay(250);
                digitalWrite(BUZZER,LOW);
                if (DEBUG) Serial.println("ALERTA: Mesa niveladora LLEGO a posición superior");                                          
                }
          if (digitalRead(SENSOR_TOP1)||digitalRead(SENSOR_TOP2)) {
                analogWrite(MOTOR_PWM,SPEED_LOW);
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
// Ejecuta el comando recibido desde el puerto Serial1 (RS485)
//-------------------------------------------------
void Exec_Command_Rx_RS485() {
    switch (command_RS485) {
            case 'S' : 
                       if (value_RS485==0) SERIAL_ACTION = SERIAL_SAMPLE_NEXT;    // CAMBIO DE MUESTRA (NEXT)
                       if (value_RS485==1) SERIAL_ACTION = SERIAL_SAMPLE_CYCLE;   // CAMBIO A POSICION INICIAL  
                       break;
            case 'H' : 
                       if (value_RS485==0) SERIAL_ACTION = SERIAL_DOOR_OPEN;      // ABRIR TAPA BLINDAJE
                       if (value_RS485==1) SERIAL_ACTION = SERIAL_DOOR_CLOSE;     // CERRAR TAPA DE BLINDAJE
                       break;
            case 'P' : 
                       if (value_RS485==0) SERIAL_ACTION = SERIAL_TABLE_DOWN;     // BAJAR MESA NIVELADORA
                       if (value_RS485==1) SERIAL_ACTION = SERIAL_TABLE_UP;       // SUBIR MESA NIVELADORA
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
boolean Check_Line_Rx_RS485() {
    if ( Serial1.available() > 0 ) {
        RxChar_RS485 = Serial1.read();
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


