#include "electrovalve.hpp"
#include <Arduino.h>


void init_vanne(electrovalve_array_t *valve_array){
  for(int i = 0 ; i < ELECTROVALVE_SIZE;i++){
    PRINT(("CONFIGURE VALVE "+i));
    struct electrovalve valve = valve_array->array[i];
    pinMode(valve.pin,OUTPUT);
  }
}
 void open(struct electrovalve *valve ){
  PRINT("OPEN VALVE: "+valve->pin);
  digitalWrite(valve->pin,HIGH);
 }

 
 void close(struct electrovalve *valve){
    PRINT("CLOSE VALVE: "+valve->pin);
    digitalWrite(valve->pin,LOW);
  }


 void openTime(struct electrovalve *valve,uint32_t duration){
  open(valve);
  PRINT("WAIT VALVE: "+valve->pin+" Duration: "+duration);
  delay(duration);
  close(valve);
}


electrovalve_array_t electrovalve_list ={
  .array={
    [0] = {0,PIN_ELECTROVALVE_0},
    [1] = {1,PIN_ELECTROVALVE_1},
    [2] = {2,PIN_ELECTROVALVE_2},
    [3] = {3,PIN_ELECTROVALVE_3},
    [4] = {4,PIN_ELECTROVALVE_4},
    [5] = {5,PIN_ELECTROVALVE_5}
  },
  .init = init_vanne,
  .open = open,
  .close = close,
  .openTime = openTime
};
