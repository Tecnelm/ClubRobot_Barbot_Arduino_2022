#include "chariot.hpp"
#include <Servo.h>
#include <Arduino.h>

Servo servo_chariot;


void setup() {

}



void init_chariot(chariot_t *chariot){
  servo_chariot.attach(SERVO_PIN);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);
  pinMode(CAPTEUR1, INPUT_PULLUP);
  pinMode(CAPTEUR2, INPUT_PULLUP);
  pinMode(CAPTEUR3, INPUT_PULLUP);
  pinMode(CAPTEUR4, INPUT_PULLUP);
}

void move_right(){
  int motorValue;
  sens=vers_droite;
  digitalWrite(MOTOR_PIN2, LOW);
  for(int motorValue = 0 ; motorValue <= 250; motorValue +=10){
    digitalWrite(MOTOR_PIN1, motorValue); 
    delay(30);
   ]
}

void move_left(){
  int motorValue;
  sens=vers_gauche;
  digitalWrite(MOTOR_PIN1, LOW);
  for(int motorValue = 0 ; motorValue <= 250; motorValue +=RAMP_INCREASE){
    digitalWrite(MOTOR_PIN2, motorValue); 
    delay(RAMP_DELAY);
  }
}

void hold(){ 
  int motorValue;
  if (sens==vers_droite){
    digitalWrite(MOTOR_PIN2, LOW);
    for(int motorValue = 250 ; motorValue >= 0; motorValue -=RAMP_INCREASE){
      digitalWrite(MOTOR_PIN1, motorValue); 
      delay(RAMP_DELAY);
    }
  } else if (sens==vers_gauche){
    digitalWrite(MOTOR_PIN1, LOW);
    for(int motorValue = 250 ; motorValue >= 0; motorValue -=RAMP_INCREASE){
      digitalWrite(MOTOR_PIN2, motorValue); 
      delay(RAMP_DELAY);
    }
  }
  // pas nécessaire mais par sécurité je l'ai mis
  else if (sens==arret){
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
  }
}


void move_position(chariot_t *chariot,uint8_t position){
  if (chariot.position > position){
    move_right();
  } else if(chariot.position < position){
    move_left(); 
  } else {
    hold();
  }
}



void check(chariot_t *chariot){
  
  if (digitalread(CAPTEUR1) == 1){
    position = 1;
  }
  if (digitalread(CAPTEUR2) == 1){
    position = 2;
  }
  if (digitalread(CAPTEUR3) == 1){
    position = 3;
  }
  if (digitalread(CAPTEUR4) == 1){
    position = 4;
  }
}

// Pour vider dans le verre
void pour(chariot_t *chariot){
        servo_chariot.write(ANGLE_MAX);  
        delay(POUR_TIME); // temps chariot abaissé
        servo_chariot.write(ANGLE_MIN); 
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
