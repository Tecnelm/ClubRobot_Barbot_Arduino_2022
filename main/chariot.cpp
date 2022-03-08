#include "chariot.hpp"
#include <Servo.h>
#include <Arduino.h>

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
  }
  PRINT("Charriot : Test STOP function end");

  
}

void move_position(chariot_t *chariot,char position){

  PRINT("Charriot : Test Move to defined prosition function start; position = "+String(position,DEC));
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
  }
  while (chariot->position != position)
  { 
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }
  chariot->stop(chariot);

  PRINT("Charriot : Test Move to defined prosition function end; position = "+String(position,DEC));

  
}

void check(chariot_t *chariot){
  
  for(int i = 0 ; i < SENSOR_POSITION_SIZE ; i ++)
  {
    if (!digitalRead(chariot->sensor_position_array[i]))
    {
      chariot->position = i;
      PRINT("Charriot : Test check position ; position = "+i);
      return;
    }
  }
}

// Pour vider dans le verre
void pour(chariot_t *chariot){
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


chariot_t chariot={
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


void test_charriot(chariot_t *chariot)
{
  PRINT("Charriot : Begin Test");
  
  chariot->init(chariot);
  PRINT("Charriot : Test right/left");

  for(int i = 0 ; i<5 ; i++)
    chariot->right(chariot);
  for(int i = 0 ; i<10 ; i++)
    chariot->left(chariot);
  for(int i = 0 ; i<5 ; i++)
    chariot->right(chariot);

  delay(5000);
  PRINT("Charriot : Test deplacement");

  for(int i = 0 ; i<10 ; i++)
  {
    chariot->left(chariot);
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }
  delay(2000);
  for(int i = 0 ; i<20 ; i++)
  {
    chariot->right(chariot);
    chariot->move(chariot);
    delay(GAME_DELAY_CHECK);
  }
  delay(2000);
  PRINT("Charriot : Test stop");

  chariot->stop(chariot);
  
  delay(5000);
  PRINT("Charriot : Test pour");
  chariot->pour(chariot);

  PRINT("Charriot : Move to position 3");
  chariot->move_position(chariot,2);
  PRINT("Charriot : test END");

  pinMode(PIN_RIGHT_BUTTON,INPUT_PULLUP);
  pinMode(PIN_LEFT_BUTTON,INPUT_PULLUP);
  int current = millis();
  PRINT("Charriot : test MANUAL INPUT");
  while(1)
  {
    
    if(millis() - current  > GAME_DELAY_CHECK)
    {
        current = millis();
        if(!digitalRead(PIN_RIGHT_BUTTON) && !digitalRead(PIN_LEFT_BUTTON))
        {

        }else if (!digitalRead(PIN_RIGHT_BUTTON))
        {
            chariot->right(chariot);

        }else if (!digitalRead(PIN_LEFT_BUTTON))
        {
           chariot->left(chariot);
        }
        else
        {
            if (chariot->way == WAY_RIGHT){
                chariot->left(chariot);
            }
            else if (chariot->way == WAY_LEFT)
            {
                chariot->right(chariot);
            }
        }
        chariot->move(chariot);
        
    }

  }

}