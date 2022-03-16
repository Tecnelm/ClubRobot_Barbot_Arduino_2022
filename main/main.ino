#include "config.h"
#include "game.hpp"
#include "test.hpp"

extern game_t game;
void setup() {
  #ifdef DEBUG
    test_init();
  #else
    game.init(&game);
  #endif

}

void loop() {
  
  #ifdef DEBUG
    test_loop();
  #else
    switch (game.state)
    {
      case GAME_STATE_IDDLE:
        game.iddle(&game);
      break;
      case GAME_STATE_RUN:
        game.run(&game);
      break;
      case GAME_STATE_END:
        game.end(&game);
      break;
      case GAME_STATE_RESET:
        game.reset(&game);
      break;
    }
    game->communication->check_message(game->communication);

  #endif
}
