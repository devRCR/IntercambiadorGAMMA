#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include "Hardware_NodeSlave.h"



int us_delay = 1000;

boolean FLAG_GO_POS1,FLAG_GO_POS2,FLAG_GO_POS3
boolean FLAG_RUNNING_MANUAL;
boolean DIRECTION;
boolean GO_FULL_RIGHT;
int PosActual = 0;


//Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

//Configura software serial para sensor ultrasónico
SoftwareSerial mySerial(13,8); // RX, TX
unsigned char data[4]={};
float distance;

// Variables de temporización
unsigned long MillisPrevio = 0;
unsigned long MillisActual = 0;

unsigned long MillisTestPrevio = 0;
unsigned long MillisTestActual = 0;

//====================================================================
//  S E T U P 
//====================================================================
void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);

  FLAG_GO_POS1 = false;
  FLAG_GO_POS2 = false;
  FLAG_GO_POS3 = false;
  GO_FULL_RIGHT = false;
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

  pinMode(BTN_CLAW_OPEN,INPUT);
  pinMode(BTN_CLAW_CLOSE,INPUT);  
  pinMode(BTN_MARI_CATCH,INPUT);  
  pinMode(BTN_MARI_RELEASE,INPUT);

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

    if (!digitalRead(BTN_CLAW_OPEN))  digitalWrite(RELAY,LOW);
    if (!digitalRead(BTN_CLAW_CLOSE)) digitalWrite(RELAY,HIGH);

    if (!digitalRead(BTN_GO_POS1)) {
                FLAG_RUNNING_MANUAL = true;
                MillisActual = millis();
                DIRECTION = DirLeft;
                digitalWrite(M_EN,LOW);
                MoveOneStep();
                }
                
    if (!digitalRead(BTN_GO_POS2)) {
                FLAG_RUNNING_MANUAL = true;
                MillisActual = millis();
                DIRECTION = DirRight;
                digitalWrite(M_EN,LOW);
                MoveOneStep();
                }

    if (!digitalRead(BTN_MARI_CATCH)) {
//          if (!digitalRead(SENS_CLAW_OPEN)) {
//              lcd.setCursor(0,0);  
//              lcd.print("NOTHING.....");
//          }
//          else {
//              lcd.setCursor(0,0);  
//              lcd.print("DETECT......");
//          }
                if ((digitalRead(SENS_MAR1)) and
                    (digitalRead(SENS_MAR2)) and
                    (digitalRead(SENS_MAR3))) {
                          digitalWrite(BUZZER,HIGH);
                          delay(250);
                          digitalWrite(BUZZER,LOW);
                          delay(250);
                          digitalWrite(BUZZER,HIGH);
                          delay(250);
                          digitalWrite(BUZZER,LOW);
                          delay(250);
                          }
                     else {
                          FLAG_RUNNING_MANUAL = true;
                          MillisActual = millis();
                          DIRECTION = DirRight;
                          digitalWrite(M_EN,LOW);
                          MoveOneStep();
                     }
                }

    if (!digitalRead(BTN_MARI_RELEASE)) {
                if ((digitalRead(SENS_RING01)) or
                    (digitalRead(SENS_RING02)) or
                    (digitalRead(SENS_RING03))) {
                          digitalWrite(BUZZER,HIGH);
                          delay(250);
                          digitalWrite(BUZZER,LOW);
                          delay(250);
                          digitalWrite(BUZZER,HIGH);
                          delay(250);
                          digitalWrite(BUZZER,LOW);
                          delay(250);
                          digitalWrite(BUZZER,HIGH);
                          delay(250);
                          digitalWrite(BUZZER,LOW);
                          delay(250); 
                          }
                     else {
                          FLAG_RUNNING_MANUAL = true;
                          MillisActual = millis();
                          DIRECTION = DirRight;
                          digitalWrite(M_EN,LOW);
                          MoveOneStep();
                     }
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


  
//    do{
//     for(int i=0;i<4;i++)
//     {
//       data[i]=mySerial.read();
//     }
//  }while(mySerial.read()==0xff);
//
//  mySerial.flush();
//
//  if(data[0]==0xff)
//    {
//      int sum;
//      sum=(data[0]+data[1]+data[2])&0x00FF;
//      if(sum==data[3])
//      {
//        distance=(data[1]<<8)+data[2];
//        if(distance>30)
//          {
//           Serial.print("distance=");
//           Serial.print(distance/10);
//           Serial.println("cm");
//          }else 
//             {
//               Serial.println("Below the lower limit");
//             }
//      }else Serial.println("ERROR");
//     }
//     delay(100);

  
//   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
//  lcd.setCursor(0, 1);
//   // Escribimos el número de segundos trascurridos
//  //lcd.print(millis()/1000);
//  //lcd.print(" Segundos");
//  //delay(1000);
//  //digitalWrite(RELAY,HIGH); 
//  //delay(1000);
//  //digitalWrite(RELAY,LOW); 
//  
//  if (!digitalRead(BTN_GO_POS1)) lcd.print("BOTON GO 1  ");
//  if (!digitalRead(BTN_GO_POS2)) lcd.print("BOTON GO 2  ");
//  if (!digitalRead(BTN_GO_POS3)) lcd.print("BOTON GO 3  ");
//  if (!digitalRead(BTN_STOP))    lcd.print("BOTON PARADA");  
//  
//  if (!digitalRead(BTN_OPEN_CLAW))         lcd.print("OPEN CLAW ");
//  if (!digitalRead(BTN_CLOSE_CLAW))        lcd.print("CLOSE CLAW"); 
//  if (!digitalRead(BTN_CATCH_MARINELLI))   lcd.print("CATCH     ");
//  if (!digitalRead(BTN_RELEASE_MARINELLI)) lcd.print("RELEASE   ");  
//
//  if (!digitalRead(BTN_GENERAL1))         lcd.print("BTN GEN_01");
//  if (!digitalRead(BTN_GENERAL2))         lcd.print("BTN GEN_02"); 
//  if (!digitalRead(BTN_GENERAL3))         lcd.print("BTN GEN_03");
//  if (!digitalRead(BTN_GENERAL4))         lcd.print("BTN GEN_04");  
//  
//  delay(200);

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

  
