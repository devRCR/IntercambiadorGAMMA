// DEFINE LOS PUERTOS SERIALES
// ---------------------------
#define       SerialNodeMaster     Serial1

// PINES PANTALLA LCD
#define     LCD_RS    43
#define     LCD_RW    44
#define     LCD_EN    45
#define     LCD_D4    50
#define     LCD_D5    51
#define     LCD_D6    52
#define     LCD_D7    53

// PINS MOTOR HUSILLO
#define     M_EN      A1
#define     M_DIR     A2
#define     M_STEP    A3
#define     DirRight  HIGH
#define     DirLeft   LOW 

// VELOCIDAD
#define SENS_SPEED    A4

// PIN CONTROL RELAY
#define     RELAY     A0

// PIN CONTROL BUZZER
#define     BUZZER    42

// SENSORES DETECTOR MARINELLI GARRA
#define   SENS_MAR1   A5
#define   SENS_MAR2   A6
#define   SENS_MAR3   A7

// ANILLO INFERIOR DE SENSORES
#define   SENS_RING01   A8
#define   SENS_RING02   A9
#define   SENS_RING03   A10

// SENSORES DE HUSILLO
#define   SENS_POS1   12
#define   SENS_POS2   11
#define   SENS_POS3   10

// SENSORES MAGNETICOS GARRA
#define   SENS_CLAW_OPEN    35
#define   SENS_CLAW_CLOSE   36

// BOTONES DE MOVIMIENTO DEL HUSILLO
#define   BTN_GO_POS1     27
#define   BTN_GO_POS2     28
#define   BTN_GO_POS3     29
#define   BTN_STOP        30

// BOTONES DE CONTROL GARRA
#define   BTN_MARI_CATCH_TOP      22
#define   BTN_MARI_RELEASE_TOP    23
#define   BTN_MARI_CATCH_BOTTOM   24
#define   BTN_MARI_RELEASE_BOTTOM 25

// BOTONES GENERALES
#define   BTN_GENERAL1    38
#define   BTN_GENERAL2    39
#define   BTN_GENERAL3    40
#define   BTN_GENERAL4    41

// JUMPERS
#define   JUMPER1     A12
#define   JUMPER2     A12
#define   JUMPER3     A12
#define   JUMPER4     A12


#define   FLAG_STOP                   0
#define   FLAG_GO_POS_01             10
#define   FLAG_GO_POS_02             20
#define   FLAG_GO_POS_03             30
#define   FLAG_MARI_CATCH_TOP        40
#define   FLAG_MARI_CATCH_BOTTOM     45
#define   FLAG_MARI_RELEASE_TOP      50
#define   FLAG_MARI_RELEASE_BOTTOM   55

#define   SERIAL_NONE                1000
#define   SERIAL_STOP                   0
#define   SERIAL_GO_POS_01             10
#define   SERIAL_GO_POS_02             20
#define   SERIAL_GO_POS_03             30
#define   SERIAL_MARI_CATCH_TOP        40
#define   SERIAL_MARI_CATCH_BOTTOM     45
#define   SERIAL_MARI_RELEASE_TOP      50
#define   SERIAL_MARI_RELEASE_BOTTOM   55


