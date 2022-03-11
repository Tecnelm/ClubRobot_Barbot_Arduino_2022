#include "chariot.hpp"
#include <Servo.h>
#include <Arduino.h>

#define sign(value) (value <0 ? -1:1)

Servo servo_chariot;


void init_chariot(chariot_t *chariot){
  servo_chariot.attach(PIN_SERVO);
  pinMode(PIN_1_MOTOR, OUTPUT);
  pinMode(PIN_2_MOTOR, OUTPUT);
  pinMode(PIN_EN_MOTOR,OUTPUT);
  for(int i = 0 ; i < SENSOR_POSITION_SIZE; i++)
  {
    pinMode(chariot->sensor_position_array[i],INPUT_PULLUP);
  }
  servo_chariot.write(SERVO_ANGLE_MIN);

}

void charriot_right(chariot_t *chariot){
  chariot->speed -= MOTOR_SLICE_VALUE;
  chariot->speed = chariot->speed < -MOTOR_MAX_VALUE ? -MOTOR_MAX_VALUE:chariot->speed;
  PRINT("Charriot : move RIGHT value = "+chariot->speed);
}

void charriot_left(chariot_t *chariot){
  chariot->speed += MOTOR_SLICE_VALUE;
  chariot->speed = chariot->speed > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE:chariot->speed;
  PRINT("Charriot : move LEFT value = "+chariot->speed);

}

void choose_way(chariot_t *chariot){
  if(chariot->speed> -MOTOR_SLICE_VALUE && chariot->speed <MOTOR_SLICE_VALUE)
  {
    if (chariot->way != WAY_STOP)
    {
      chariot->way = WAY_STOP;
      chariot->speed = 0;
      digitalWrite(PIN_1_MOTOR, LOW);
      digitalWrite(PIN_2_MOTOR, LOW);
      analogWrite(PIN_EN_MOTOR,chariot->speed); 
      PRINT("Charriot : STOP MOTOR");
    }

  }else if (chariot -> speed < 0)
  {
    if(chariot->way != WAY_RIGHT)
    {
      chariot->way = WAY_RIGHT;
      digitalWrite(PIN_2_MOTOR, LOW);
      digitalWrite(PIN_1_MOTOR, HIGH);
    }
    analogWrite(PIN_EN_MOTOR,-(chariot->speed)); 
    PRINT("Charriot : Set MOTOR RIGHT value = "+-chariot->speed);

  }else if (chariot->speed > 0)
  {
    if(chariot->way != WAY_LEFT)
    {
      chariot->way = WAY_LEFT;
      digitalWrite(PIN_1_MOTOR, LOW);
      digitalWrite(PIN_2_MOTOR, HIGH);
    }
    analogWrite(PIN_EN_MOTOR,(chariot->speed)); 
    PRINT("Charriot : Set MOTOR LEFT value = "+((chariot->speed)));
  }
  chariot->check(chariot);
}

void charriot_stop(chariot_t *chariot)
{
  PRINT("Charriot : Test STOP function start");
  while (chariot->way !=WAY_STOP)
  {
    if(chariot->way == WAY_RIGHT)
      chariot->left(chariot);
    else
      chariot->right(chariot);
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }
  PRINT("Charriot : Test STOP function end");

  
}

void move_position(chariot_t *chariot,char position){

  PRINT("Charriot : Test Move to defined prosition function start; position = "+String(position,DEC));
  chariot->stop(chariot);
  for(int i = 0  ; i < MOTOR_MOVE_POSITION_MULTIPLE; i++)
  {
    if(chariot->position > position)
    {
      chariot->right(chariot);

    }else if (chariot->position < position)
    {
      chariot->left(chariot);
    }
    else //chariot trigger position
    {
      break;
    }
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }
  while (chariot->position != position) /// continue mouvement 
  { 
    chariot->check(chariot);
    delay(GAME_DELAY_CHECK);
  }
  while (chariot->multiple_position)
  {
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }  
  PRINT("Charriot : Test Move to defined prosition function end; position = "+String(position,DEC));
}

void chariot_check(chariot_t *chariot){
  chariot->multiple_position = -1;
  switch (chariot->way)
  {
  case WAY_RIGHT:
    for(int i = SENSOR_POSITION_SIZE-1 ; i >= 0; i--)
    {
      if (!digitalRead(chariot->sensor_position_array[i]))
      {
        chariot->multiple_position++;
        chariot->position = i;
        PRINT("Charriot : Test check position ; position = "+i);
      }
    }
    break;
  case WAY_LEFT:
    for(int i = 0 ; i < SENSOR_POSITION_SIZE ; i ++)
    {
      if (!digitalRead(chariot->sensor_position_array[i]))
      {
        chariot->multiple_position++;
        chariot->position = i;
        PRINT("Charriot : Test check position ; position = "+i);
      }
    }
    break;
  }
}

// Pour vider dans le verre
void chariot_pour(chariot_t *chariot){
        PRINT("Charriot : Test POUR;DOWN");
        for(int i = SERVO_ANGLE_MIN ; i<= SERVO_ANGLE_MAX ; i++)
        {
          servo_chariot.write(i);
          delay(SERVO_DELAY_MS);
        } 
        PRINT("Charriot : Test POUR ; wait");
        delay(POUR_TIME_MS); // temps chariot abaissé
        PRINT("Charriot : Test POUR ; UP");
        for(int i = SERVO_ANGLE_MAX ; i>= SERVO_ANGLE_MIN ; i--)
        {
          servo_chariot.write(i);
          delay(SERVO_DELAY_MS);
        }
        PRINT("Charriot : Test POUR;END");

}


void chariot_center(chariot_t *chariot)
{ 
  char position = GAME_POSITION_CENTER;
  chariot->move_position(chariot,position);

  PRINT("Charriot : SLOW SPEED TO REACH CENTER");
  char sign = sign(chariot->speed);


  while((chariot->speed)*sign> MOTOR_CENTER_SPEED_VALUE-MOTOR_SLICE_VALUE && (chariot->speed)*sign < MOTOR_CENTER_SPEED_VALUE+MOTOR_SLICE_VALUE)
  {
    switch (chariot->way)
    {
    case WAY_RIGHT:
      chariot->left(chariot);
      break;
    case WAY_LEFT:
      chariot->right(chariot);
      break;
    }
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }

    switch (chariot->way)
  {
    case WAY_RIGHT:
      position++;
      break;
    
    case WAY_LEFT:
      position++;
    break;
  }
  
  chariot->speed = MOTOR_CENTER_SPEED_VALUE * sign;
  while (chariot->position != position) /// continue mouvement 
  { 
    chariot->check(chariot);
    delay(GAME_DELAY_CHECK);
  }

  PRINT("Charriot : WAIT SINGLE BUTTON");
  while(chariot->multiple_position)
  {
    chariot->check(chariot);
    delay(GAME_DELAY_CHECK);
  };

  PRINT("Charriot : STOPING MOUVEMENT");
  chariot->stop(chariot);
}

chariot_t chariot={
  .position = 0,
  .multiple_position = 0,
  .way= WAY_STOP,
  .speed = 0,
  .sensor_position_array = {
    PIN_SENSOR_POSITION_0,
    PIN_SENSOR_POSITION_1,
    PIN_SENSOR_POSITION_2,
    PIN_SENSOR_POSITION_3,
    PIN_SENSOR_POSITION_4,
    PIN_SENSOR_POSITION_5
  },
  .init=init_chariot,
  .right = charriot_right,
  .left = charriot_left,
  .stop = charriot_stop,
  .move_position=move_position,
  .move=choose_way,
  .check = chariot_check,
  .pour=chariot_pour,
  .center = chariot_center,
  };
