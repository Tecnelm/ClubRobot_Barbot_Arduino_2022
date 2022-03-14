#include "config.h"
#ifdef DEBUG
    #include "chariot.hpp"
    #include "electrovalve.hpp"
    #include "game.hpp"
    #include "tank.hpp"

    #ifndef TEST_H
    #define TEST_H
    extern chariot_t chariot;
    extern electrovalve_array_t electrovalves;
    extern tank_t tank;
    extern communication_t communication;

    extern game_t game;

    void test_pump(game_t *game);
    void test_charriot(chariot_t *chariot);
    void test_tank(tank_t *tank);
    void test_electrovalves(electrovalve_array_t *electrovalves);
    void test_charriot(chariot_t *chariot);
    void test_init();
    void test_loop();

    #endif
#endif
