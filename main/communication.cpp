#include "communication.hpp"
#include <Arduino.h>
#include <stdio.h>

void init_serial()
{
  Serial.begin(BAUDRATES);
  Serial.setTimeout(TIMEOUT_SERIAL);
  while(!Serial){
    ;
  }

  PRINT("SERIAL OK");
}

void check_serial_message(communication_t *communication)
{
  char c;
  String commande;
  if (Serial.available())
  {
    commande = Serial.readStringUntil('}') + "}";
    Serial.flush();
    commande.toCharArray(communication->buffer, BUFFERSIZE);
    parse_message(communication->buffer,commande.length());
  }
}

void parse_message(char *buffer, uint8_t size){
  Serial.print(create_commande(COMMANDE_DEBUG_STR,buffer));
  int commande;
  int value;
  if(sscanf((char*)buffer,"{commande:%d;value:%d}",&commande,&value) == 2)
  {
      switch(commande)
      {
        case COMMANDE_SEND_POSITION:
        break;
      }
  }
  else
    Serial.println(create_commande(COMMANDE_RESPONSE,STATUS_ERROR));
}