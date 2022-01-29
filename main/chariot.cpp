#include "chariot.hpp"
#include <Servo.h>

Servo servo_chariot;



void init(chariot_t *chariot){

}

void move_right(){

}

void move_left(){

}

void move_position(chariot_t *chariot,uint8_t position){

}

void check(chariot_t *chariot){

}

void pour(chariot_t *chariot){

}



static chariot_t chariot={
  .position = 0,
  .init=init,
  .move_right = move_right,
  .move_left = move_left,
  .move_position=move_position,
  .check = check,
  .pour=pour
  };

