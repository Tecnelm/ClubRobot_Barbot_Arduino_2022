#include <stdint.h>

#ifndef ELECTROVALVE_H
#define ELECTROVALVE_H

#define ELECTROVALVE_SIZE 6

struct electrovalve {
  uint8_t id;
  uint8_t pin;
};

struct worker_event_electrovalve
{
  struct electrovalve electrovalve;
  uint64_t timeStart;
  uint32_t duration;

  void (*start)(struct worker_event_electrovalve);
  void (*stop)(struct worker_event_electrovalve);
};

struct worker_electrovalve
{
  struct worker_event_electrovalve event_array[ELECTROVALVE_SIZE];
  void (*add_event)(struct worker_event_electrovalve *event);
  void (*worker_check)();
};


typedef struct {

  struct electrovalve electrovalve_array[ELECTROVALVE_SIZE];    
  void (*init)();
  void (*open)(struct electrovalve );
  void (*close)(struct electrovalve);
  void (*openTime)(struct electrovalve,uint32_t duration);

  struct worker_electrovalve electrovalve_worker;

}electrovalve_array_t;



#endif