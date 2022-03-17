#include "callback.hpp"
#include "chariot.hpp"
#include "config.h"


void on_game_stop_receive(game_t *game,int value)
{

        PRINT("Callback : stop");
        game->communication->send_command(COMMANDE_STOP_GAME,STATUS_KO);
        if (game->state == GAME_STATE_RUN)
        {
            game->state = GAME_STATE_END;
            game->end(game,value);
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

void on_start_receive(game_t *game,int value)
{
    if (value == STATUS_OK)
    {
        if(game->state == GAME_STATE_IDDLE)
            game->state = GAME_STATE_RUN;
    }
}


