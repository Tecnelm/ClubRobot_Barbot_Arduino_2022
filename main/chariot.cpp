#include "chariot.hpp"
#include <Servo.h>
#include <Arduino.h>

Servo servo_chariot;


void init_chariot(chariot_t *chariot){
  servo_chariot.attach(PIN_SERVO);
  pinMode(PIN_1_MOTOR, OUTPUT);
  pinMode(PIN_2_MOTOR, OUTPUT);
  for(int i = 0 ; i < SENSOR_POSITION_SIZE; i++)
  {
    pinMode(chariot->sensor_position_array[i],INPUT_PULLUP);
  }
}

void charriot_right(chariot_t *chariot){
  chariot->speed += MOTOR_SLICE_VALUE;
  delay(SLICE_DELAY_MS);
}

void charriot_left(chariot_t *chariot){
  chariot->speed -= MOTOR_SLICE_VALUE;
  delay(SLICE_DELAY_MS);
}

void choose_way(chariot_t *chariot){
  if(chariot->speed> -MOTOR_SLICE_VALUE && chariot->speed <MOTOR_SLICE_VALUE)
  {
    chariot->way = WAY_STOP;
    chariot->speed = 0;
    analogWrite(PIN_1_MOTOR, LOW);
    analogWrite(PIN_2_MOTOR, LOW);

  }else if (chariot -> speed >0)
  {
    chariot->speed = chariot->speed >255 ? 255:chariot->speed;
    chariot->way = WAY_RIGHT;
    analogWrite(PIN_2_MOTOR, LOW);
    analogWrite(PIN_1_MOTOR,chariot->speed); 
  }else if (chariot->speed < 0)
  {
    chariot->speed = chariot->speed < -255 ? -255:chariot->speed;
    chariot->way = WAY_LEFT;

    analogWrite(PIN_1_MOTOR, LOW);
    analogWrite(PIN_2_MOTOR,-(chariot->speed)); 

  }
}

void charriot_stop(chariot_t *chariot)
{
  while (chariot->way !=WAY_STOP)
  {
    if(chariot->way == WAY_RIGHT)
      chariot->left(chariot);
    else
      chariot->right(chariot);
    chariot->move(chariot);
  }
  
}

void move_position(chariot_t *chariot,char position){

  chariot->stop(chariot);
  for(int i = 0  ; i < MOTOR_MOVE_POSITION_MULTIPLE ; i++)
  {
    if(chariot->position > position)
    {
      chariot->right(chariot);
    }else if (chariot->position < position)
    {
      chariot->left(chariot);
    }
    else
    {
      break;
    }
    chariot->move(chariot);
    chariot->check(chariot);
  }
  while (chariot->position != position)
  { 
    chariot->move(chariot);
    chariot->check(chariot);
    delay(DELAY_CHECK_MOVE_POSITION);
  }
  chariot->stop(chariot);
  
}

void check(chariot_t *chariot){
  
  for(int i = 0 ; i < SENSOR_POSITION_SIZE ; i ++)
  {
    if (digitalRead(chariot->sensor_position_array[i]))
    {
      chariot->position = i;
      return;
    }
  }
}

// Pour vider dans le verre
void pour(chariot_t *chariot){
        for(int i = SERVO_ANGLE_MIN; i < SERVO_ANGLE_MAX ; i++)
        {
          servo_chariot.write(i);  
          delay(SERVO_DELAY_MS); // temps chariot abaissé
        }
        delay(POUR_TIME_MS); // temps chariot abaissé
        for(int i = SERVO_ANGLE_MAX ; i >= SERVO_ANGLE_MIN ; i--)
        {
          servo_chariot.write(i);  
          delay(SERVO_DELAY_MS); // temps chariot abaissé
        } 
}



static chariot_t chariot={
  .position = 0,
  .way= WAY_STOP,
  .speed = 0,
  .sensor_position_array = {
    PIN_SENSOR_POSITION_0,
    PIN_SENSOR_POSITION_1,
    PIN_SENSOR_POSITION_2,
    PIN_SENSOR_POSITION_3
  },
  .init=init_chariot,
  .right = charriot_right,
  .left = charriot_left,
  .stop = charriot_stop,
  .move_position=move_position,
  .move=choose_way,
  .check = check,
  .pour=pour
  };
