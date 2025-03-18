// DEFINE LOS PUERTOS SERIALES
// ---------------------------
#define       SerialNodeWheel     Serial1
#define       SerialNodeSpindle   Serial2


// DEFINE BOTONES DE HARDWARE
// --------------------------
#define       BTN_SAMPLE_NEXT   30
#define       BTN_SAMPLE_CYCLE  31
#define       BTN_PLATE_DOWN    32
#define       BTN_PLATE_UP      33
#define       BTN_SHIELD_OPEN   34
#define       BTN_SHIELD_CLOSE  35

#define       BTN_STOP              36
#define       BTN_GO_POS_1          37
#define       BTN_GO_POS_2          38
//#define       BTN_GO_POS_3        39
#define       BTN_MARI_CATCH_TOP    40
#define       BTN_MARI_RELEASE_TOP  41

// DEFINE COMANDOS PARA EL NODE WHEEL
// ----------------------------------
#define       CMD_SAMPLE_NEXT   "S1"
#define       CMD_SAMPLE_CYCLE  "S0"
#define       CMD_SHIELD_OPEN   "H0"
#define       CMD_SHIELD_CLOSE  "H1"
#define       CMD_PLATE_DOWN    "P0"
#define       CMD_PLATE_UP      "P1"


// DEFINE COMANDOS PARA EL NODE SPINDLE
// ------------------------------------
#define       CMD_STOP                "T0"
#define       CMD_GO_POS_1            "G1"
#define       CMD_GO_POS_2            "G2"
#define       CMD_GO_POS_3            "G3"
#define       CMD_MARI_CATCH_TOP      "C0"
#define       CMD_MARI_CATCH_BOTTOM   "C1"
#define       CMD_MARI_RELEASE_TOP    "R0"
#define       CMD_MARI_RELEASE_BOTTOM "R1"

