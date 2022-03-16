#include <Arduino.h>
#include "tank.hpp"
#include "config.h"


void tank_init(struct tank* tank)
{
  pinMode(tank->pump,OUTPUT);
  digitalWrite(tank->pump,CLOSE);
  pinMode(tank->sensor,INPUT);
  tank->refill_tank(tank);
}

void refill_tank(struct tank* tank)
{
  if (digitalRead(tank->sensor))
  {
    PRINT("START REFILL MAIN TANK");
    digitalWrite(tank->pump,OPEN);
    while(digitalRead(tank->sensor))
      delay(GAME_DELAY_CHECK);
    digitalWrite(tank-> pump,CLOSE);
    PRINT("END REFILLING MAIN TANK");
  }
  
}

tank_t tank = {
  .init = tank_init,
  .refill_tank = refill_tank,
  .pump = PIN_TANK_PUMP,
  .sensor = PIN_TANK_SENSOR
};
