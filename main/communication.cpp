#include "communication.hpp"
#include <stdio.h>
#include "callback.hpp"

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
  if (Serial.available())
  {
    c = Serial.read();
    PRINT(""+c);
    communication->buffer[communication->index++] = c;
    if(c == '}' || communication->index>= BUFFERSIZE-2)
    {
       communication->buffer[communication->index] = '\0';
       parse_message(communication->buffer,communication->index);
       communication->index = 0;
    }
  }
}

void parse_message(char *buffer, char size){
  PRINT("PARSE MESSAGE = " + buffer);
  int commande;
  int value;
  if(sscanf((char*)buffer,"{commande=%d;value=%d}",&commande,&value) == 2)
  {
      PRINT("PARSE MESSAGE = " + "OK");
      switch(commande)
      {
        case COMMANDE_SEND_POSITION:
          on_position_receive(&game,value);
        break;
        case COMMANDE_STOP_GAME:
          on_game_stop_receive(&game,value);
        break;
        case COMMANDE_START_GAME:
          on_start_receive(&game,value);
        default:
          PRINT("PARSE MESSAGE = " + "UNIMPLEMENTED");
      }
  }
  else
  {
    PRINT("PARSE MESSAGE = " + "KO");
    Serial.println(create_commande(COMMANDE_RESPONSE,STATUS_ERROR));
  }
    
}

void communication_send_command(command_t command,status_t status)
{
  if(Serial)
  {
    Serial.print(create_commande(command,status));
  }
}
void communication_send_command_str(String str)
{
  if(Serial)
  {
    Serial.print(create_commande(COMMANDE_DEBUG_STR,str));
  }
}
communication_t communication={
  .buffer = communication_receive_buffer,
  .index = 0,
  .init = init_serial,
  .check_message=check_serial_message,
  .send_command = communication_send_command,
  .send_command_str =  communication_send_command_str
};
