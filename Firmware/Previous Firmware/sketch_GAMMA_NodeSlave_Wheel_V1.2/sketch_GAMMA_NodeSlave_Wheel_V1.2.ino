#include "Hardware_NodeSlave_Wheel.h"

int RUNNING = 0;
boolean DEBUG = true;

// Decodificación de trama recibida desde puerto Serial 1 (485)
char RxChar_RS485 = 0;
String RxString_RS485 = "";
char command_RS485 = 0;
int value_RS485 = 0;

void setup() {
  // Configura el puerto Serial 1 para
  // comunicación RS-485 con los otros nodos
  pinMode(CONTROL_RS485,OUTPUT);
  digitalWrite(CONTROL_RS485,MODE_RX);
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
    
  pinMode(RLY_B1_R01,OUTPUT);
  digitalWrite(RLY_B1_R01,HIGH);
  pinMode(RLY_B1_R02,OUTPUT);
  digitalWrite(RLY_B1_R02,HIGH);
  pinMode(RLY_B1_R03,OUTPUT);
  digitalWrite(RLY_B1_R03,HIGH);
  pinMode(RLY_B1_R04,OUTPUT);
  digitalWrite(RLY_B1_R04,HIGH);
  pinMode(RLY_B1_R05,OUTPUT);
  digitalWrite(RLY_B1_R05,HIGH);
  pinMode(RLY_B1_R06,OUTPUT);
  digitalWrite(RLY_B1_R06,HIGH);
  pinMode(RLY_B1_R07,OUTPUT);
  digitalWrite(RLY_B1_R07,HIGH);
  pinMode(RLY_B1_R08,OUTPUT);
  digitalWrite(RLY_B1_R08,HIGH);

  pinMode(RLY_B2_R01,OUTPUT);
  digitalWrite(RLY_B2_R01,HIGH);
  pinMode(RLY_B2_R02,OUTPUT);
  digitalWrite(RLY_B2_R02,HIGH);
  pinMode(RLY_B2_R03,OUTPUT);
  digitalWrite(RLY_B2_R03,HIGH);
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
    
////----------------------------------------------------
//// CAMBIO DE MUESTRA
//    if (!digitalRead(BTN_NEXT)) {
//        if (digitalRead(SENSOR_TOP1) or digitalRead(SENSOR_TOP2)){
//            digitalWrite(RLY_B1_R01,LOW);
//            delay(1000);
//            while (!digitalRead(SENS_ORANGE));
//            digitalWrite(RLY_B1_R01,HIGH);
//            digitalWrite(BUZZER,HIGH);
//            delay(250);
//            digitalWrite(BUZZER,LOW); 
//            if (DEBUG) Serial.println("NEXT completado"); 
//            delay(1000);                
//            }
//        }
////----------------------------------------------------
//// ABRIR TAPA BLINDAJE (D11)
//    if (!digitalRead(BTN_OPEN)) {
//        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
//              // Sólo se abre la tapa si los dos sensores del plato
//              // elevador se encuentran activados en la parte inferior
//                {
//                digitalWrite(RLY_B2_R01,LOW);
//                while (!digitalRead(SENS_GREEN));
//                digitalWrite(RLY_B2_R01,HIGH); 
//                if (DEBUG) Serial.println("ALERTA: Tapa de blindaje totalment abierta");
//                }
//           else {
//                digitalWrite(BUZZER,HIGH);
//                delay(1000);
//                digitalWrite(BUZZER,LOW);
//                if (DEBUG) Serial.println("ERROR: Mesa niveladora no se encuentra en posicion inferior");
//                }
//    }
////----------------------------------------------------
//// CERRAR TAPA BLINDAJE (D12)
//    if (!digitalRead(BTN_CLOSE)) {
//        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
//              // Sólo se cierra la tapa si los dos sensores del plato
//              // elevador se encuentran activados en la parte inferior
//                {
//                digitalWrite(RLY_B2_R02,LOW);
//                while (!digitalRead(SENS_BLUE));
//                digitalWrite(RLY_B2_R02,HIGH);
//                if (DEBUG) Serial.println("ALERTA: Tapa de blindaje totalment cerrada");       
//                }
//           else {
//                digitalWrite(BUZZER,HIGH);
//                delay(1000);
//                digitalWrite(BUZZER,LOW);
//                if (DEBUG) Serial.println("ERROR: Mesa niveladora NO se encuentra en posicin inferior");
//                }
//    }
//
//  if (!digitalRead(BTN_DOWN)) {
//          if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) {
//                for (int i=1; i<=3; i++) {
//                      digitalWrite(BUZZER,HIGH);
//                      delay(200);
//                      digitalWrite(BUZZER,LOW);
//                      delay(200);
//                      }
//                if (DEBUG) Serial.println("ALERTA: Mesa niveladora YA en encuentra en posición inferior");
//                }
//          else {
//                digitalWrite(DRIVER_IN1,HIGH);
//                digitalWrite(DRIVER_IN2,LOW);
//                analogWrite(MOTOR_PWM,SPEED_HIGH);
//                RUNNING = 1;
//                }
//          }
//          
//  if (!digitalRead(BTN_UP)) {
//          if (digitalRead(SENS_BLUE)) {
//                 if (digitalRead(SENSOR_TOP1)&&digitalRead(SENSOR_TOP2)) {
//                              for (int i=1; i<=3; i++) {
//                                    digitalWrite(BUZZER,HIGH);
//                                    delay(200);
//                                    digitalWrite(BUZZER,LOW);
//                                    delay(200);
//                                    }
//                              if (DEBUG) Serial.println("ALERTA: Mesa niveladora YA en encuentra en posición superior");
//                              }
//                        else  {
//                              digitalWrite(DRIVER_IN1,LOW);
//                              digitalWrite(DRIVER_IN2,HIGH);
//                              analogWrite(MOTOR_PWM,SPEED_HIGH);
//                              RUNNING = 2;
//                              }
//                         }
//            else {
//                 digitalWrite(BUZZER,HIGH);
//                 delay(1000);
//                 digitalWrite(BUZZER,LOW);          
//                 }
//          }
//
//  if (RUNNING==1) {
//          if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) {
//                digitalWrite(DRIVER_IN1,LOW);
//                digitalWrite(DRIVER_IN2,LOW);
//                RUNNING = 0; 
//                analogWrite(MOTOR_PWM,SPEED_HIGH); 
//                digitalWrite(BUZZER,HIGH);
//                delay(250);
//                digitalWrite(BUZZER,LOW);
//                if (DEBUG) Serial.println("ALERTA: Mesa niveladora LLEGO a posición inferior");
//                }
//          if (digitalRead(SENSOR_BOTTOM1)||digitalRead(SENSOR_BOTTOM2)) {
//                analogWrite(MOTOR_PWM,SPEED_LOW);
//                }
//          }
//  if (RUNNING==2) {
//          if (digitalRead(SENSOR_TOP1)&&digitalRead(SENSOR_TOP2)) {
//                digitalWrite(DRIVER_IN1,LOW);
//                digitalWrite(DRIVER_IN2,LOW);
//                RUNNING = 0; 
//                analogWrite(MOTOR_PWM,SPEED_HIGH); 
//                digitalWrite(BUZZER,HIGH);
//                delay(250);
//                digitalWrite(BUZZER,LOW);
//                if (DEBUG) Serial.println("ALERTA: Mesa niveladora LLEGO a posición superior");                                          
//                }
//          if (digitalRead(SENSOR_TOP1)||digitalRead(SENSOR_TOP2)) {
//                analogWrite(MOTOR_PWM,SPEED_LOW);
//                }
//          }    
 
//  delay(retardo);
//  digitalWrite(RLY_B1_R01,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R01,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R02,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R02,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R03,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R03,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R04,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R04,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R05,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R05,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R06,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R06,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R07,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R07,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R08,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B1_R08,HIGH); 
//  
//  delay(retardo);
//  digitalWrite(RLY_B2_R01,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R01,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R02,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R02,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R03,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R03,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R04,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R04,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R05,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R05,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R06,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R06,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R07,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R07,HIGH);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R08,LOW);  
//  delay(retardo);
//  digitalWrite(RLY_B2_R08,HIGH);  
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
            case 's' : digitalWrite(BUZZER,HIGH);
                       delay(100);
                       digitalWrite(BUZZER,LOW);
                       digitalWrite(CONTROL_RS485,MODE_TX);
                       Serial1.println("s1000");
                       digitalWrite(CONTROL_RS485,MODE_RX); 
                       break;
            case 'g' : 
                       digitalWrite(CONTROL_RS485,MODE_TX);
                       Serial1.println("g2000");
                       digitalWrite(CONTROL_RS485,MODE_RX); 
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
                       digitalWrite(CONTROL_RS485,MODE_TX);
                       Serial1.println(RxChar_RS485);
                       digitalWrite(CONTROL_RS485,MODE_RX); 
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


