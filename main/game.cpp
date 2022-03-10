#include "game.hpp"
#include "Arduino.h"


void game_init(game_t *game)
{
    for(int i = 0 ; i < BUTTON_SIZE ; i++)
    {
        pinMode(game->button[i],INPUT_PULLUP);
    }
    pinMode(game->main_pump,OUTPUT);

    game->communication->init();
    game->chariot->init(game->chariot);
    game->electrovalve->init(game->electrovalve);
    game->tank->init(game->tank);

    digitalWrite(game->main_pump,OPEN);
    game->lastcheck = millis();
    game->state = GAME_STATE_IDDLE;    
    
}
void game_run(game_t *game)
{
    if(millis() - game->lastcheck  > GAME_DELAY_CHECK)
    {
        game->lastcheck = millis();
        if(!digitalRead(game->button[0]) && !digitalRead(game->button[1]))
        {

        }else if (!digitalRead(game->button[0]))
        {
            game->chariot->right(game->chariot);

        }else if (!digitalRead(game->button[1]))
        {
           game->chariot->left(game->chariot);
        }
        else
        {
            if (game->chariot->way == WAY_RIGHT){
                game->chariot->left(game->chariot);
            }
            else if (game->chariot->way == WAY_LEFT)
            {
                game->chariot->right(game->chariot);
            }
        }
        game->chariot->move(game->chariot);
        
    }
    game->communication->check_message(game->communication);

}
void game_iddle(game_t *game)
{
    if(millis() - game->lastcheck  > GAME_DELAY_CHECK)
    {
        game->lastcheck = millis();

        if(analogRead(game->sharp_sensor) > THRESHOLD_GLASS_PRESENT) {
            game->state = GAME_STATE_RUN;
            game->communication->send_command(COMMANDE_START_GAME,STATUS_NONE);
        }
        
    }
}
void game_reset(game_t *game)
{
    game->chariot->left(game->chariot);
    game->chariot->move(game->chariot);
    game->chariot->left(game->chariot);
    game->chariot->move(game->chariot);
    game->chariot->left(game->chariot);
    game->chariot->move(game->chariot);
    delay(1000);
    game->chariot->move_position(game->chariot,3);

    game->tank->refill_tank(game->tank);
}
void game_end(game_t *game)
{
    game->communication->send_command(COMMANDE_STOP_GAME,STATUS_NONE);
    game->chariot->move_position(game->chariot,GAME_POSITION_CENTER);
    game->chariot->pour(game->chariot);
    game->tank->refill_tank(game->tank);
}



game_t game ={
    .lastcheck = 0,
    .state = GAME_STATE_INIT,
    .chariot = &chariot,
    .communication = &communication,
    .electrovalve = &electrovalves,
    .tank = &tank,
    .button = {
        PIN_RIGHT_BUTTON,
        PIN_LEFT_BUTTON
    },
    .main_pump = PIN_MAIN_PUMP,
    .sharp_sensor =PIN_SENSOR_SHARP, 
    .init = game_init,
    .run = game_run,
    .iddle = game_iddle,
    .reset = game_reset,
    .end = game_end
};

