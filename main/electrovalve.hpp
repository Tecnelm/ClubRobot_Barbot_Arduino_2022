#include <stdint.h>
#include "config.h"
#ifndef ELECTROVALVE_H
#define ELECTROVALVE_H



struct electrovalve {
  uint8_t id;
  uint8_t pin;
};

typedef struct electrovalve_array{

  struct electrovalve array[ELECTROVALVE_SIZE];    
  void (*init)(struct electrovalve_array *valve_array);
  void (*open)(struct electrovalve *valve );
  void (*close)(struct electrovalve *valve);
  void (*openTime)(struct electrovalve *valve,uint32_t duration);

}electrovalve_array_t;



#endif