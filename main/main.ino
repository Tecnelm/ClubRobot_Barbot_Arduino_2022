
#include "game.hpp"

extern game_t game;

void setup() {
  game.init();
}

void loop() {
  
  switch (game.state)
  {
    case GAME_STATE_IDDLE:
      game.iddle();
    break;
    case GAME_STATE_RUN:
      game.run();
    break;
    case GAME_STATE_RESET:
      game.reset();
    break;
  }

}
