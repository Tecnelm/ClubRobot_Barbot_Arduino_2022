#include "electrovalve.hpp"
#include <Arduino.h>


void init_vanne(electrovalve_array_t *valve_array){
  for(int i = 0 ; i < ELECTROVALVE_SIZE;i++){
    PRINT(("CONFIGURE VALVE "+String(i,DEC)));
    struct electrovalve valve = valve_array->array[i];
    pinMode(valve.pin,OUTPUT);
  }
}
 void open(struct electrovalve *valve ){
  PRINT("OPEN VALVE: "+String(valve->pin,DEC));
  digitalWrite(valve->pin,OPEN);
 }

 
 void close(struct electrovalve *valve){
    PRINT("CLOSE VALVE: "+String(valve->pin,DEC));
    digitalWrite(valve->pin,CLOSE);
  }


 void openTime(struct electrovalve *valve,int duration){
  open(valve);
  PRINT("WAIT VALVE: "+String(valve->pin,DEC)+" Duration: "+String(duration,DEC));
  delay(duration);
  close(valve);
}


electrovalve_array_t electrovalves ={
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

void test_electrovalves()
{
  PRINT("ELECTROVALVE SETUP TEST");
  electrovalves.init(&electrovalves);
  PRINT("ELECTROVALVE ACTIVATION TEST");
  for(int a = 0 ; a<3 ; a++)
  {
    PRINT("ELECTROVALVE OPEN TEST");
    for( int i = 5 ; i >=0 ; i-- )
    {
      electrovalves.open(&electrovalves.array[i]);
      delay(500);
    }
    PRINT("ELECTROVALVE CLOSE TEST");
    for( int i = 0 ; i <=6 ; i++ )
    {
      electrovalves.close(&electrovalves.array[i]);
      delay(500);
    }
    PRINT("ELECTROVALVE OPEN-TIME TEST");
    for( int i = 0 ; i <=6 ; i++ )
    {
      electrovalves.openTime(&electrovalves.array[i],500);
      
    }
  }
  PRINT("ELECTROVALVE END TEST");

}

