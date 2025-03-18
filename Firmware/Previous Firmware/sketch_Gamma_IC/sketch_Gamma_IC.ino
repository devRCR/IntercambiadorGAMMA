// <<<<<<  FIRMWARE DE CONTROL  >>>>>>>
// CONTROL DE ESCANER LINEAL
// O. Baltuano
// Ver 2.0.1 - 25-abril-2022
// Ver 2.0.5 - 11-mayo-2002
//             Se incluyó información de posición actual
//             Se activo movimiento del slider


//--- MENSAJES ENVIADOS A LA PC ---
//---
// m10 : Detenido normal ('s')
// m11 : Detenido por usuario ('b')
// m12 : Detenido en Home ('f')
// m13 : Detenido en límite derecho ('g')

// m21 : Moviendo hacia derecha ('d')
// m22 : Moviendo hacia izquierda ('c')
// m23 : Buscando sensor derecho ('a')
// m24 : Moviendo hacia Home ('e')

// m30 : Número de pasos inválido ('h')
// m31 : Imposible mover. Límite derecho alcanzado ('j')

// m90 : Comando no reconocido ('x')
//----------------------------------


//#define SENSOR1 2    // Sensor lado derecho (motor)
//#define SENSOR2 3    // Sensor lado izquierdo
#define DIR     2
#define STEP    3
#define ENABLE  4

#define DirRight   HIGH
#define DirLeft    LOW 

// Decodificación de trama recibida desde la PC
char RxChar = 0;
String RxString = "";
char command = 0;
int value = 0;

boolean DIRECTION;

boolean FLAG_RUNNING;
boolean GO_FULL_RIGHT;
boolean GO_HOME;
int us_delay = 1500;
int StepsPending = 0;
int StepToGoHome = 980;
int PosActual = 0;

void setup() {
  pinMode(ENABLE,OUTPUT);
  pinMode(STEP,OUTPUT);
  pinMode(DIR,OUTPUT);
  digitalWrite(ENABLE,HIGH);
  digitalWrite(STEP,HIGH);
  DIRECTION = DirLeft;
  digitalWrite(DIR,DIRECTION);
  Serial.begin(9600);
  FLAG_RUNNING = false;
  GO_FULL_RIGHT = false;
  GO_HOME = false;
}

void loop() {
    if (FLAG_RUNNING) {
                  MoveOneStep();
                  StepsPending--;
                  if (StepsPending == 0) {
                        FLAG_RUNNING = false;
                        digitalWrite(ENABLE,HIGH);
                        Serial.println("m10"); 
                        // m10 : Detenido normal
                        Serial.print('p');
                        Serial.println(PosActual);
                        }
        } 
    if (Check_Line_Rx()) Exec_Command_Rx();
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
              Serial.print('p');
              Serial.println(PosActual);  
              }
        }
}

// ------------------------------------------------
// Ejecuta el comando recibido
//-------------------------------------------------
void Exec_Command_Rx() {
    switch (command) {
            case 's' : 
                       FLAG_RUNNING = false;
                       digitalWrite(ENABLE,HIGH);
                       Serial.println("m11"); 
                       // m11 : Detenido por usuario
                       Serial.print('p');
                       Serial.println(PosActual);                       
                       break;
            case 'l' : 
                       DIRECTION = DirLeft;
                       if (value>0 ) {
                            FLAG_RUNNING = true;
                            digitalWrite(ENABLE,LOW);
                            StepsPending = value;
                            Serial.println("m22"); 
                            // m22 : Moviendo hacia izquierda
                            }
                       break;
            case 'r' : 
                       DIRECTION = DirRight;
                       if (value>0) {
                             FLAG_RUNNING = true;
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


