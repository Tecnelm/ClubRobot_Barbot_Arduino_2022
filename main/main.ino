
#include "game.hpp"
#include "electrovalve.hpp"

extern game_t game;


void setup() {
  game.init(&game);
  test_electrovalves();
}

void loop() {
  
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

}
