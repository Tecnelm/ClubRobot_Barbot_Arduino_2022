
#include <stdint.h>

#ifndef CHARIOT_H
#define CHARIOT_H

#define POSITION_CENTER 0

#define SERVO_PIN 7
//Ports de commande du moteur B
#define MOTOR_PIN1 8
#define MOTOR_PIN2 9
#define ENABLE_PIN 6

#define BOUTON_DROIT_PIN 12
#define BOUTON_GAUCHE_PIN 13
#define CAPTEUR1 2
#define CAPTEUR2 3
#define CAPTEUR3 4
#define CAPTEUR4 5

// Pour vider dans le verre
#define ANGLE_MIN 0
#define ANGLE_MAX 180
#define POUR_TIME 5000

// rampes de commandes pour accélération du moteur, 30ms entre chaque augmentation, 25 paliers de 10 = 250
#define RAMP_INCREASE 10
#define RAMP_DELAY 30


enum sens {
  vers_droite;
  vers_gauche;
  arret;
};



typedef struct chariot
{
  uint8_t position;  
  void (*init)(struct chariot *chariot);
  void (*move_right)();
  void (*move_left)();
  void (*move_position)(struct chariot *chariot,uint8_t position);
  void (*check)(struct chariot *chariot);
  void (*pour)(struct chariot *chariot);
  void (*hold)();
}chariot_t;

#endif
