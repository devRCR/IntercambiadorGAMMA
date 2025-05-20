#ifndef COMMAND_DEFINITIONS_H
#define COMMAND_DEFINITIONS_H

// Comandos esperados
#define CMD_SHIELD    'H'
#define CMD_PLATE     'P'
#define CMD_SAMPLE    'S'
#define CMD_STOP       'T'

// Valores binarios estándar
#define VAL_OPEN       0
#define VAL_CLOSE      1
#define VAL_STOP        0

// Alias legibles
#define VAL_SHIELD_OPEN     VAL_OPEN
#define VAL_SHIELD_CLOSE    VAL_CLOSE

#define VAL_PLATE_UP        VAL_OPEN
#define VAL_PLATE_DOWN      VAL_CLOSE

#define VAL_SAMPLE_PREV     VAL_OPEN
#define VAL_SAMPLE_NEXT     VAL_CLOSE

#endif
