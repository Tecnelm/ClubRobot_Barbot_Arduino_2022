#pragma once

typedef struct tank {
  void (*init)(struct tank* tank);
  void (*refill_tank)(struct tank* tank);
  const int pump;
  const int sensor;

}tank_t;

void test_tank();

