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
  uint8_t character;
  for (uint8_t index = 0 ; Serial.available() && index <BUFFERSIZE-1 ; index++)
  {
    character = Serial.read();
    PRINT("COM : RECEIVE = "+character);
    communication->buffer[index] = character;
    if (character == END_COMMAND_CHAR)
    {
      communication->buffer[index+1] = '\0';
      parse_message(communication->buffer, index+1);
    }
  }
}

void parse_message(uint8_t *buffer, uint8_t size){
  PRINT("COM : MESSAGE = "+(char*)buffer);
  uint8_t test[10];
  uint8_t value;
  if(sscanf((char*)buffer,"{COMMAND:%s;value:%d}",test,&value) == 2)
  {
    PRINT("COMMANDE : "+(char*)test);
    PRINT("VALUE= "+value);
  }
  else
  PRINT("ERROR DECODE COMMANDE");



}