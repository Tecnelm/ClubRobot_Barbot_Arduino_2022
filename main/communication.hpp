#include "config.h"
#include <stdint.h>

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

typedef struct communication
{
  static uint8_t buffer[BUFFERSIZE];
  void (*init)();
  void (*check_message)(struct communication *communication);
  
}communication_t;

void parse_message(uint8_t *buffer, uint8_t size);

#endif 