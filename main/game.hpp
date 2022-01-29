

#ifndef GAME_H
#define GAME_H


enum state {
  GAME_STATE_INIT, 
  GAME_STATE_IDDLE,
  GAME_STATE_RUN,
  GAME_STATE_RESET,
  GAME_STATE_COUNT
};

typedef struct game {

  enum state state;
  void (*init)();
  void (*run)();
  void (*iddle)();
  void (*reset)();

} game_t;

#endif