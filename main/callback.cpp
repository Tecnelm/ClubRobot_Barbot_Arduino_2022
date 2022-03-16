#include "callback.hpp"
#include "chariot.hpp"
#include "config.h"


void on_game_stop_receive(game_t *game,int value)
{
    if (value == STATUS_OK)
    {
        PRINT("Callback : stop");
        game->state = GAME_STATE_END;
    }
}


void on_position_receive(game_t *game,int value)
{
    if (value < SENSOR_POSITION_SIZE)
    {
        PRINT("Callback : position");

        if(digitalRead(game->chariot->sensor_position_array[value]))
        {
            PRINT("Callback : position : OK");
            game->communication->send_command(COMMANDE_SEND_POSITION,STATUS_OK);
            game->electrovalve->openTime(&(game->electrovalve->array[value]),TIME_ELECTROVALVE_OPEN_MS);
        }
        else
            game->communication->send_command(COMMANDE_SEND_POSITION,STATUS_KO);

    }
}
