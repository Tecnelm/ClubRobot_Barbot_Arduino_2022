
#include "config.h"

#ifndef CHARIOT_H
#define CHARIOT_H

typedef enum way 
{
  WAY_RIGHT,
  WAY_LEFT,
  WAY_STOP
} way_t;


typedef struct chariot
{
  char position;  
  way_t way; 
  int speed;
  char sensor_position_array[SENSOR_POSITION_SIZE];
  void (*init)(struct chariot *chariot);
  void (*right)(struct chariot *chariot);
  void (*left)(struct chariot *chariot);
  void (*stop)(struct chariot *chariot);
  void (*move_position)(struct chariot *chariot,char position);
  void (*move)(struct chariot *chariot);
  void (*check)(struct chariot *chariot);
  void (*pour)(struct chariot *chariot);
}chariot_t;


void test_charriot(chariot_t *chariot);
#endif
