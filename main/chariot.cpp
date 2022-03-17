#include "chariot.hpp"
#include <Servo.h>
#include <Arduino.h>

#define sign(value) (value < 0 ? -1 : 1)


void init_chariot(chariot_t *chariot)
{
  pinMode(PIN_1_MOTOR, OUTPUT);
  pinMode(PIN_2_MOTOR, OUTPUT);
  pinMode(PIN_EN_MOTOR, OUTPUT);
  for (int i = 0; i < SENSOR_POSITION_SIZE; i++)
  {
    pinMode(chariot->sensor_position_array[i], INPUT_PULLUP);
  }
  pinMode(chariot->sensor_FDC[0], INPUT_PULLUP);
  pinMode(chariot->sensor_FDC[1], INPUT_PULLUP);


  chariot->way = WAY_LEFT;
  chariot->check(chariot);
  chariot->way = WAY_STOP;
}

void charriot_right(chariot_t *chariot)
{
  if (!(digitalRead(chariot->sensor_position_array[0])))
  {
    if (chariot->way == WAY_LEFT)
    {
      double tmp = chariot->speed * DIVIDE_SPEED;
      chariot->speed = int(tmp);
    }
    else
    {

      PRINT("SPEED RIGHT= " + chariot->speed);
      if (chariot->way == WAY_STOP)
        chariot->speed -= MOTOR_MIN_VALUE;
      chariot->speed -= MOTOR_SLICE_VALUE;

      chariot->speed = chariot->speed < -MOTOR_MAX_VALUE ? -MOTOR_MAX_VALUE : chariot->speed;
      PRINT("SPEED RIGHT= " + chariot->speed);
    }
  }
  else
  {
    if (chariot->way != WAY_STOP)
    {
      double tmp = chariot->speed * DIVIDE_SPEED;
      chariot->speed = int(tmp);
    }
  }

  PRINT("Charriot : move RIGHT value = " + chariot->speed);
}

void charriot_left(chariot_t *chariot)
{
  if (!(digitalRead(chariot->sensor_position_array[5])))
  {
    if (chariot->way == WAY_RIGHT)
    {
      double tmp = chariot->speed * DIVIDE_SPEED;
      chariot->speed = int(tmp);
    }
    else
    {
      PRINT("SPEED LEFT = " + chariot->speed);

      if (chariot->way == WAY_STOP)
        ;
      chariot->speed += MOTOR_MIN_VALUE;
      chariot->speed += MOTOR_SLICE_VALUE;

      PRINT("SPEED LEFT = " + chariot->speed);
      chariot->speed = chariot->speed > MOTOR_MAX_VALUE ? MOTOR_MAX_VALUE : chariot->speed;
      PRINT("Charriot : move LEFT value = " + chariot->speed);
    }
  }
  else
  {
    if (chariot->way != WAY_STOP)
    {
      double tmp = chariot->speed * DIVIDE_SPEED;
      chariot->speed = int(tmp);
    }
  }
}

void choose_way(chariot_t *chariot)
{

  if (!fdc(chariot))
  {
    if (sign(chariot->speed) * chariot->speed < MOTOR_MIN_VALUE)
    {
      if (chariot->way != WAY_STOP)
      {
        chariot->way = WAY_STOP;
        chariot->speed = 0;
        digitalWrite(PIN_1_MOTOR, LOW);
        digitalWrite(PIN_2_MOTOR, LOW);
        analogWrite(PIN_EN_MOTOR, chariot->speed);
        PRINT("Charriot : STOP MOTOR");
      }
    }
    else if (chariot->speed < 0)
    {
      if (chariot->way != WAY_RIGHT)
      {
        chariot->way = WAY_RIGHT;
        digitalWrite(PIN_2_MOTOR, LOW);
        digitalWrite(PIN_1_MOTOR, HIGH);
      }
      analogWrite(PIN_EN_MOTOR, -(chariot->speed));
      PRINT("Charriot : Set MOTOR RIGHT value = " + -chariot->speed);
    }
    else if (chariot->speed > 0)
    {
      if (chariot->way != WAY_LEFT)
      {
        chariot->way = WAY_LEFT;
        digitalWrite(PIN_1_MOTOR, LOW);
        digitalWrite(PIN_2_MOTOR, HIGH);
      }
      analogWrite(PIN_EN_MOTOR, (chariot->speed));
      PRINT("Charriot : Set MOTOR LEFT value = " + ((chariot->speed)));
    }
  }
  chariot->check(chariot);
}

void charriot_stop(chariot_t *chariot)
{
  PRINT("Charriot : Test STOP function start");
  chariot->speed = 0;
  analogWrite(PIN_EN_MOTOR,chariot->speed);
  PRINT("Charriot : Test STOP function end");
}

void move_position(chariot_t *chariot, char position)
{
  way_t way;
  PRINT("Charriot : Test Move to defined prosition function start; position = " + String(position, DEC));
  chariot->stop(chariot);
  
  if (chariot->position > position)
  {
    digitalWrite(PIN_2_MOTOR, LOW);
  digitalWrite(PIN_1_MOTOR, HIGH);  
  analogWrite(PIN_EN_MOTOR,MOTOR_CENTER_SPEED_VALUE );
  }
  else if (chariot->position < position)
  {
    digitalWrite(PIN_2_MOTOR, HIGH);
    digitalWrite(PIN_1_MOTOR, LOW);  
    analogWrite(PIN_EN_MOTOR,MOTOR_CENTER_SPEED_VALUE );
  }

  while (!digitalRead(chariot->sensor_position_array[position])) /// continue mouvement
  {
    delay(1);
  }
  chariot->stop(chariot);

  PRINT("Charriot : Test Move to defined prosition function end; position = " + String(position, DEC));
}

void chariot_check(chariot_t *chariot)
{
  chariot->multiple_position = -1;
  switch (chariot->way)
  {
  case WAY_RIGHT:
    for (int i = SENSOR_POSITION_SIZE - 1; i >= 0; i--)
    {
      if (digitalRead(chariot->sensor_position_array[i]))
      {
        chariot->multiple_position++;
        chariot->position = i;
        PRINT("Charriot : Test check position ; position = " + i);
      }
    }
    break;
  case WAY_LEFT:
    for (int i = 0; i < SENSOR_POSITION_SIZE; i++)
    {
      if (digitalRead(chariot->sensor_position_array[i]))
      {
        chariot->multiple_position++;
        chariot->position = i;
        PRINT("Charriot : Test check position ; position = " + i);
      }
    }
    break;
  }
}

// Pour vider dans le verre
void chariot_pour(chariot_t *chariot)
{
  PRINT("Charriot : Test POUR;DOWN");
  for (int i = SERVO_ANGLE_MIN; i <= SERVO_ANGLE_MAX; i++)
  {
    delay(SERVO_DELAY_MS);
  }
  PRINT("Charriot : Test POUR ; wait");
  delay(POUR_TIME_MS); // temps chariot abaissé
  PRINT("Charriot : Test POUR ; UP");
  for (int i = SERVO_ANGLE_MAX; i >= SERVO_ANGLE_MIN; i--)
  {
    delay(SERVO_DELAY_MS);
  }
  PRINT("Charriot : Test POUR;END");
}

int fdc(chariot_t *chariot)
{
  if (digitalRead(chariot->sensor_FDC[0]) || digitalRead(chariot->sensor_FDC[1]))
  {
    analogWrite(PIN_EN_MOTOR,0);
    digitalWrite(PIN_1_MOTOR, HIGH);
    digitalWrite(PIN_2_MOTOR, HIGH);
    PRINT("FIN DE COURSE FAIL");

    if (!digitalRead(PIN_RIGHT_BUTTON) && digitalRead(PIN_LEFT_BUTTON) && !digitalRead(chariot->sensor_FDC[0] ))
    {
      digitalWrite(PIN_1_MOTOR, HIGH);
      digitalWrite(PIN_2_MOTOR, LOW);
      analogWrite(PIN_EN_MOTOR, MOTOR_MIN_VALUE);
      delay(50);
    }
    else if (!digitalRead(PIN_LEFT_BUTTON) && digitalRead(PIN_RIGHT_BUTTON) && !digitalRead(chariot->sensor_FDC[1]))
    {
      digitalWrite(PIN_1_MOTOR, LOW);
      digitalWrite(PIN_2_MOTOR, HIGH);
      analogWrite(PIN_EN_MOTOR, MOTOR_MIN_VALUE);
      delay(50);
    }
    chariot->speed = 0;
    chariot->way = WAY_STOP;
    analogWrite(PIN_EN_MOTOR, 0);
    return 1;
  }
  return 0;
}

void chariot_center(chariot_t *chariot)
{

  chariot->move_position(chariot, GAME_POSITION_CENTER1+1);  

  digitalWrite(PIN_2_MOTOR, LOW);
  digitalWrite(PIN_1_MOTOR, HIGH);  
  analogWrite(PIN_EN_MOTOR,MOTOR_CENTER_SPEED_VALUE );
  while (!digitalRead(chariot->sensor_position_array[GAME_POSITION_CENTER]));

  chariot->stop(chariot);
  chariot->check(chariot);
  PRINT("Charriot : STOPING MOUVEMENT");
}


chariot_t chariot = {
    .position = 0,
    .multiple_position = 0,
    .way = WAY_STOP,
    .speed = 0,
    .sensor_position_array = {
        PIN_SENSOR_POSITION_0,
        PIN_SENSOR_POSITION_1,
        PIN_SENSOR_POSITION_2,
        PIN_SENSOR_POSITION_3,
        PIN_SENSOR_POSITION_4,
        PIN_SENSOR_POSITION_5},
    .sensor_FDC = {PIN_SENSOR_POSITION_FDCD, PIN_SENSOR_POSITION_FDCG},
    .init = init_chariot,
    .right = charriot_right,
    .left = charriot_left,
    .stop = charriot_stop,
    .move_position = move_position,
    .move = choose_way,
    .check = chariot_check,
    .pour = chariot_pour,
    .center = chariot_center,
};
