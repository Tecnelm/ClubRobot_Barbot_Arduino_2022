#include "game.hpp"
#include "Arduino.h"


void game_init(game_t *game)
{
    for(int i = 0 ; i < BUTTON_SIZE ; i++)
    {
        pinMode(game->button[i],INPUT_PULLUP);
    }

    game->communication->init();
    game->chariot->init(game->chariot);
    game->electrovalve->init(game->electrovalve);
    game->tank->init(game->tank);

    game->lastcheck = millis();
    game->reset(game);
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
            if(game->state_glass == SATE_GLASS_ABSENT)
            {
                game->communication->send_command(COMMANDE_STATE_GLASS,STATUS_OK);
                game->state_glass = SATE_GLASS_PRESENT;
            }
            if (!digitalRead(game->button[0] && !digitalRead(game->button[1])))
            {
                game->communication->send_command(COMMANDE_START_GAME,STATUS_OK);
                game->state = GAME_STATE_RUN;
            }
        }
        else
        {
             if(game->state_glass == SATE_GLASS_PRESENT)
            {
                game->communication->send_command(COMMANDE_STATE_GLASS,STATUS_KO);
                game->state_glass = SATE_GLASS_ABSENT;
            }
        }
        
        
    }
}
void game_reset(game_t *game)
{
    game->chariot->speed = -GAME_RESET_SPEED ;
    game->chariot->move(game->chariot);
    
    while (digitalRead(!game->chariot->sensor_position_array[0]))
    {
        game->chariot->move(game->chariot);
        delay(GAME_DELAY_CHECK);
    }
    

    game->chariot->speed = 0;
    game->chariot->move(game->chariot);
    game->tank->refill_tank(game->tank);
}
void game_end(game_t *game)
{
    game->chariot->move_position(game->chariot,GAME_POSITION_CENTER);
    game->chariot->center(game->chariot);
    game->chariot->pour(game->chariot);
    game->tank->refill_tank(game->tank);

    game->state = GAME_STATE_IDDLE;
}



game_t game ={
    .lastcheck = 0,
    .state = GAME_STATE_INIT,
    .chariot = &chariot,
    .communication = &communication,
    .electrovalve = &electrovalves,
    .tank = &tank,
    .state_glass = SATE_GLASS_ABSENT,
    .button = {
        PIN_RIGHT_BUTTON,
        PIN_LEFT_BUTTON
    },
    .sharp_sensor =PIN_SENSOR_SHARP, 
    .init = game_init,
    .run = game_run,
    .iddle = game_iddle,
    .reset = game_reset,
    .end = game_end
};

