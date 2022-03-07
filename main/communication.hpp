#include "config.h"
#include <stdint.h>

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define create_commande(commande,value) "{commande:"+(String)commande+";value:"+(String)value+"}"

typedef struct communication
{
  static char buffer[BUFFERSIZE];
  void (*init)();
  void (*check_message)(struct communication *communication);
  
}communication_t;

void parse_message(char *buffer, uint8_t size);


typedef enum {
  COMMANDE_RESPONSE,
  COMMANDE_SEND_POSITION,
  COMMANDE_START_GAME,
  COMMANDE_STOP_GAME,
  COMMANDE_DEBUG_STR
}commande_t;

typedef enum
{
  STATUS_ERROR,
  STATUS_SERIAL_CONNECTED,
  STATUS_OK,
  STATUS_KO
} status_t;


#endif 