#include <Arduino.h>
#include "tank.hpp"
#include "config.h"


void tank_init(struct tank* tank)
{
  pinMode(tank->pump,OUTPUT);
  pinMode(tank->sensor,INPUT);
}

void refill_tank(struct tank* tank)
{
  if (!digitalRead(tank->sensor))
  {
    PRINT("START REFILL MAIN TANK");
    pinMode(tank->pump,OPEN);
    while(!digitalRead(tank->sensor));
    pinMode(tank-> pump,CLOSE);
    PRINT("END REFILLING MAIN TANK");
  }
  
}

tank_t tank = {
  .init = tank_init,
  .refill_tank = refill_tank,
  .pump = PIN_TANK_PUMP,
  .sensor = PIN_TANK_SENSOR
};

void test_tank(){
  PRINT("TANK SETUP TEST");
  tank.init(&tank);
  PRINT("TANK REFILL TEST");
  tank.refill_tank(&tank);
  PRINT("TANK END TEST");
}


