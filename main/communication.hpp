#ifndef COMMUNICATION_H
#define COMMUNICATION_H


typedef struct 
{
  void (*init)();
  void (*checkMessage)();
  
}communication_t;

#endif 