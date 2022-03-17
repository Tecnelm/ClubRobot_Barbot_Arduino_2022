
#include "chariot.hpp"
#include "communication.hpp"
#include "electrovalve.hpp"
#include "tank.hpp"
#include "config.h"

#ifndef GAME_H
#define GAME_H

extern chariot_t chariot;
extern electrovalve_array_t electrovalves;
extern tank_t tank;
extern communication_t communication;

enum state {
  GAME_STATE_INIT, 
  GAME_STATE_IDDLE,
  GAME_STATE_RUN,
  GAME_STATE_END,
  GAME_STATE_RESET,
  GAME_STATE_COUNT
};

enum glass_state
{
  SATE_GLASS_ABSENT,
  SATE_GLASS_PRESENT,
  STATE_GLASS_COUNT
};

typedef struct game {
  int lastcheck;
  enum state state;
  chariot_t *chariot;
  communication_t *communication;
  electrovalve_array_t *electrovalve;
  tank_t *tank ;
  enum glass_state state_glass ;
  int button[BUTTON_SIZE];
  int sharp_sensor;
  void (*init)(struct game *game);
  void (*run)(struct game *game);
  void (*iddle)(struct game *game);
  void (*reset)(struct game *game);
  void (*end)(struct game *game,int value);


} game_t;


#endif