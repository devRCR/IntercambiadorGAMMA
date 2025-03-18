
#define     DRIVER_IN1      2
#define     DRIVER_IN2      3
#define     BUZZER          4
#define     MOTOR_PWM       5
#define     BTN_STOP        A0
#define     BTN_DOWN        A1
#define     BTN_UP          A2
#define     SENSOR_TOP1     A3
#define     SENSOR_TOP2     A4
#define     SENSOR_BOTTOM1  A5
#define     SENSOR_BOTTOM2  A6

#define     SPEED_HIGH      220
#define     SPEED_LOW       140


int RUNNING = 0;

void setup() {
  // put your setup code here, to run once:
pinMode(DRIVER_IN1,OUTPUT);
pinMode(DRIVER_IN2,OUTPUT);
pinMode(MOTOR_PWM,OUTPUT);
pinMode(BUZZER,OUTPUT);
pinMode(BTN_STOP,INPUT);
pinMode(BTN_DOWN,INPUT);
pinMode(BTN_UP,INPUT);
pinMode(SENSOR_TOP1,INPUT);
pinMode(SENSOR_TOP2,INPUT);
pinMode(SENSOR_BOTTOM1,INPUT);
pinMode(SENSOR_BOTTOM2,INPUT);

digitalWrite(BUZZER,HIGH);
delay(250);
digitalWrite(BUZZER,LOW);

analogWrite(MOTOR_PWM,SPEED_HIGH);
digitalWrite(DRIVER_IN1,LOW);
digitalWrite(DRIVER_IN2,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!digitalRead(BTN_DOWN)) {
          if (digitalRead(SENSOR_BOTTOM1)&&digitalRead(SENSOR_BOTTOM2)) {
                for (int i=1; i<=3; i++) {
                      digitalWrite(BUZZER,HIGH);
                      delay(200);
                      digitalWrite(BUZZER,LOW);
                      delay(200);
                      }
                }
          else {
                digitalWrite(DRIVER_IN1,HIGH);
                digitalWrite(DRIVER_IN2,LOW);
                analogWrite(MOTOR_PWM,SPEED_HIGH);
                RUNNING = 1;
                }
          }
  if (!digitalRead(BTN_UP)) {
          if (digitalRead(SENSOR_TOP1)&&digitalRead(SENSOR_TOP2)) {
                for (int i=1; i<=3; i++) {
                      digitalWrite(BUZZER,HIGH);
                      delay(200);
                      digitalWrite(BUZZER,LOW);
                      delay(200);
                      }
                }
          else {
                digitalWrite(DRIVER_IN1,LOW);
                digitalWrite(DRIVER_IN2,HIGH);
                analogWrite(MOTOR_PWM,SPEED_HIGH);
                RUNNING = 2;
              }
          }
  if (!digitalRead(BTN_STOP)) {
          digitalWrite(DRIVER_IN1,LOW);
          digitalWrite(DRIVER_IN2,LOW);
          RUNNING = 0;
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
                }
          if (digitalRead(SENSOR_TOP1)||digitalRead(SENSOR_TOP2)) {
                analogWrite(MOTOR_PWM,SPEED_LOW);
                }
          }
}
