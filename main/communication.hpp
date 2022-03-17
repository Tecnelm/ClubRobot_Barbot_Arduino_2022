#include "config.h"
#include <Arduino.h>

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define create_commande(commande,value) "{commande="+(String)commande+";value="+(String)value+"}"



void parse_message(char *buffer, char size);


typedef enum  {
  COMMANDE_RESPONSE,
  COMMANDE_SEND_POSITION,
  COMMANDE_START_GAME,
  COMMANDE_STOP_GAME,
  COMMANDE_DEBUG_STR,
  COMMANDE_STATE_GLASS,
  COMMANDE_COUNT
}command_t;

typedef enum 
{
  STATUS_ERROR,
  STATUS_NONE,
  STATUS_SERIAL_CONNECTED,
  STATUS_OK,
  STATUS_KO,
  STATUS_COUNT
} status_t;

static char communication_receive_buffer[BUFFERSIZE];

typedef struct communication
{
  char *buffer;
  int index;
  void (*init)();
  void (*check_message)(struct communication *communication);
  void (*send_command)(command_t command,status_t status);
  void (*send_command_str)(command_t command,int status);
  

  
}communication_t;

#endif 
