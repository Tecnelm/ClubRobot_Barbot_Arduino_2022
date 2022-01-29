
#include <stdint.h>

#ifndef CHARIOT_H
#define CHARIOT_H

#define POSITION_CENTER 0

typedef struct chariot
{
  uint8_t position;  
  void (*init)(struct chariot *chariot);
  void (*move_right)();
  void (*move_left)();
  void (*move_position)(struct chariot *chariot,uint8_t position);
  void (*check)(struct chariot *chariot);
  void (*pour)(struct chariot *chariot);

}chariot_t;

#endif