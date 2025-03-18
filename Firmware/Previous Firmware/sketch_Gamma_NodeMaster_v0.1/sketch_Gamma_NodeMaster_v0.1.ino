// <<<<<<  FIRMWARE DE CONTROL  >>>>>>>
// INTERCAMBIADOR GAMMA 
// O. Baltuano
// Ver Preliminar


//#define SENSOR1 2    // Sensor lado derecho (motor)
//#define SENSOR2 3    // Sensor lado izquierdo
#define SENS_SPEED        A0
#define ENABLE            A1
#define DIR               A2
#define STEP              A3
#define BTN_A4     A4
#define BTN_A5     A5
#define BTN_CLAW_OPEN     11
#define BTN_CLAW_CLOSE    12



#define DirRight          HIGH
#define DirLeft           LOW 

// Decodificación de trama recibida desde la PC
char RxChar = 0;
String RxString = "";
char command = 0;
int value = 0;

boolean DIRECTION;

boolean FLAG_RUNNING_AUTO;
boolean FLAG_RUNNING_MANUAL;
boolean GO_FULL_RIGHT;
boolean GO_HOME;
int us_delay = 1000;
int StepsPending = 0;
int StepToGoHome = 980;
int PosActual = 0;
int Value_Speed = 0;

// Variables de temporización
unsigned long MillisPrevio = 0;
unsigned long MillisActual = 0;

void setup() {
  pinMode(SENS_BLUE,  INPUT);
  pinMode(SENS_GREEN, INPUT);
  pinMode(SENS_VIOLET,INPUT);
  pinMode(SENS_ORANGE,INPUT);
  
  pinMode(BTN_A5,INPUT);
  pinMode(BTN_A4,INPUT);
  digitalWrite(RELAY,LOW);
  pinMode(ENABLE,OUTPUT);
  digitalWrite(ENABLE,HIGH);
  pinMode(STEP,OUTPUT);
  digitalWrite(STEP,HIGH);  
  pinMode(DIR,OUTPUT);
  DIRECTION = DirLeft;
  digitalWrite(DIR,DIRECTION);
  Serial.begin(115200);
  FLAG_RUNNING_AUTO = false;
  FLAG_RUNNING_MANUAL = false;
  GO_FULL_RIGHT = false;
  GO_HOME = false;
}

void loop() {
    if (!digitalRead(BTN_A4)or!digitalRead(BTN_A5)) {
        digitalWrite(RELAY,HIGH);
        delay(1000);
        while (!digitalRead(SENS_STEP_SWITCH));
        digitalWrite(RELAY,LOW);        
    }
//    if (FLAG_RUNNING_AUTO) {
//                  MoveOneStep();
//                  StepsPending--;
//                  if (StepsPending == 0) {
//                        FLAG_RUNNING_AUTO = false;
//                        digitalWrite(ENABLE,HIGH);
//                        Serial.println("m10"); 
//                        // m10 : Detenido normal
//                        Serial.print('p');
//                        Serial.println(PosActual);
//                        }
//        }
//    if (!digitalRead(BTN_CLAW_OPEN))  digitalWrite(SGN_CLAW_RELAY,LOW);
//    if (!digitalRead(BTN_CLAW_CLOSE)) digitalWrite(SGN_CLAW_RELAY,HIGH);
//
//    if (!digitalRead(BTN_HEAD_UP)) {
//                FLAG_RUNNING_MANUAL = true;
//                MillisActual = millis();
//                DIRECTION = DirLeft;
//                digitalWrite(ENABLE,LOW);
//                MoveOneStep();
//                }
//                
//    if (!digitalRead(BTN_HEAD_DOWN)) {
//                FLAG_RUNNING_MANUAL = true;
//                MillisActual = millis();
//                DIRECTION = DirRight;
//                digitalWrite(ENABLE,LOW);
//                MoveOneStep();
//                }
//                
//    if (FLAG_RUNNING_MANUAL) 
//                if (MillisActual - MillisPrevio < 100) {
//                    MillisPrevio = MillisActual;
//                }
//                else { 
//                    FLAG_RUNNING_MANUAL = false;
//                    digitalWrite(ENABLE,HIGH);
//                }
//    
//    if (Check_Line_Rx()) Exec_Command_Rx();
}

// Gira el motor un paso en función a la dirección
// que ha sido configurada en la variable DIRECTION
void MoveOneStep() {
    digitalWrite(DIR,DIRECTION);    // Configura la dirección 
    digitalWrite(STEP,LOW);         // 
    delayMicroseconds(500);                       // Pulso bajo de 100 us
    digitalWrite(STEP,HIGH);        //
    delayMicroseconds(us_delay);                // Retardo movimiento motor
    if (!GO_FULL_RIGHT) {
        if (DIRECTION) PosActual++;
                  else PosActual--;
        if ((PosActual % 5) == 0 ) {
              //Serial.print('p');
              //Serial.print(PosActual);
              //Serial.print(" | ");
              Value_Speed = analogRead(SENS_SPEED);
              //Serial.println(Value_Speed);
              us_delay = 1000 + 3 * Value_Speed;               
              }
        }
}

// ------------------------------------------------
// Ejecuta el comando recibido
//-------------------------------------------------
void Exec_Command_Rx() {
    switch (command) {
            case 's' : 
                       FLAG_RUNNING_AUTO = false;
                       digitalWrite(ENABLE,HIGH);
                       Serial.println("m11"); 
                       // m11 : Detenido por usuario
                       Serial.print('p');
                       Serial.println(PosActual);                       
                       break;
            case 'l' : 
                       DIRECTION = DirLeft;
                       if (value>0 ) {
                            FLAG_RUNNING_AUTO = true;
                            digitalWrite(ENABLE,LOW);
                            StepsPending = value;
                            Serial.println("m22"); 
                            // m22 : Moviendo hacia izquierda
                            }
                       break;
            case 'r' : 
                       DIRECTION = DirRight;
                       if (value>0) {
                             FLAG_RUNNING_AUTO = true;
                            digitalWrite(ENABLE,LOW);
                             StepsPending = value;
                             Serial.println("m21");
                             // m21 : Moviendo hacia derecha
                             }
                       break;
            case 'd' : 
                       if ( value>500 && value<=10000) us_delay = value;
                       break;
            case '?' :
                       Serial.println("SLR01-v2.0.5");
                       break;
            default  : 
                       Serial.println("m90"); 
                       // m90 : Comando no reconocido ('x')
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


