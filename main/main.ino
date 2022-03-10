
#include "game.hpp"
#include "electrovalve.hpp"
#include "chariot.hpp"
extern game_t game;
extern chariot_t chariot;


void setup() {
  // game.init(&game);
  // test_electrovalves();
  Serial.begin(9600);
  while (!Serial);
  Serial.println("OK");
  test_charriot(&chariot);
}

void loop() {
  
  // switch (game.state)
  // {
  //   case GAME_STATE_IDDLE:
  //     game.iddle(&game);
  //   break;$
  //   case GAME_STATE_RUN:
  //     game.run(&game);
  //   break;
  //   case GAME_STATE_END:
  //     game.end(&game);
  //   break;
  //   case GAME_STATE_RESET:
  //     game.reset(&game);
  //   break;
  // }

}
