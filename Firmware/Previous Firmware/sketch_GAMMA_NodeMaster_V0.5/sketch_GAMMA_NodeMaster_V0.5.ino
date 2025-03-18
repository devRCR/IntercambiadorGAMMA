#define     RLY_B1_R01    22
#define     RLY_B1_R02    23
#define     RLY_B1_R03    24
#define     RLY_B1_R04    25
#define     RLY_B1_R05    26
#define     RLY_B1_R06    27
#define     RLY_B1_R07    28
#define     RLY_B1_R08    29

#define     RLY_B2_R01    46
#define     RLY_B2_R02    47
#define     RLY_B2_R03    48
#define     RLY_B2_R04    49
#define     RLY_B2_R05    50
#define     RLY_B2_R06    51
#define     RLY_B2_R07    52
#define     RLY_B2_R08    53

#define     retardo   250

#define SENS_BLUE     10
#define SENS_GREEN     9
#define SENS_VIOLET    8
#define SENS_ORANGE    7

#define BTN_NEXT      3
#define BTN_CYCLE     4
#define BTN_UP        5
#define BTN_DOWN      6
#define BTN_OPEN     11
#define BTN_CLOSE    12

#define     SENSOR_TOP1     40  //A3
#define     SENSOR_TOP2     41  //A4
#define     SENSOR_BOTTOM1  42  //A5
#define     SENSOR_BOTTOM2  43  //A6

#define     BUZZER          A2  //4
#define     DRIVER_IN1      A1  //2
#define     DRIVER_IN2      A0  //3
#define     MOTOR_PWM        2  //5

#define     SPEED_HIGH     230
#define     SPEED_LOW      140

int RUNNING = 0;
boolean DEBUG = true;

void setup() {
  // put your setup code here, to run once:
  if (DEBUG) Serial.begin(115200);
  delay(2000);
  
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
// CAMBIO DE MUESTRA
    if (!digitalRead(BTN_NEXT)) {
        if (digitalRead(SENSOR_TOP1) or digitalRead(SENSOR_TOP2)){
            digitalWrite(RLY_B1_R01,LOW);
            delay(1000);
            while (!digitalRead(SENS_ORANGE));
            digitalWrite(RLY_B1_R01,HIGH);
            digitalWrite(BUZZER,HIGH);
            delay(250);
            digitalWrite(BUZZER,LOW); 
            if (DEBUG) Serial.println("NEXT completado"); 
            delay(1000);                
            }
        }
//----------------------------------------------------
// ABRIR TAPA BLINDAJE (D11)
    if (!digitalRead(BTN_OPEN)) {
        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
              // Sólo se abre la tapa si los dos sensores del plato
              // elevador se encuentran activados en la parte inferior
                {
                digitalWrite(RLY_B2_R01,LOW);
                while (!digitalRead(SENS_GREEN));
                digitalWrite(RLY_B2_R01,HIGH); 
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
    if (!digitalRead(BTN_CLOSE)) {
        if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) 
              // Sólo se cierra la tapa si los dos sensores del plato
              // elevador se encuentran activados en la parte inferior
                {
                digitalWrite(RLY_B2_R02,LOW);
                while (!digitalRead(SENS_BLUE));
                digitalWrite(RLY_B2_R02,HIGH);
                if (DEBUG) Serial.println("ALERTA: Tapa de blindaje totalment cerrada");       
                }
           else {
                digitalWrite(BUZZER,HIGH);
                delay(1000);
                digitalWrite(BUZZER,LOW);
                if (DEBUG) Serial.println("ERROR: Mesa niveladora NO se encuentra en posicin inferior");
                }
    }

  if (!digitalRead(BTN_DOWN)) {
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
          
  if (!digitalRead(BTN_UP)) {
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
