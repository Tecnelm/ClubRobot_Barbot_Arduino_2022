#include <Arduino.h>
#include "test.hpp"
#ifdef DEBUG

void test_init()
{
//    #ifdef DEBUG_STR
//        Serial.begin(BAUDRATES);
//        Serial.setTimeout(TIMEOUT_SERIAL);
//        while(!Serial){
//            ;
//        }
//        PRINT("SERIAL OK");
//    #endif
}
void test_loop()
{
    //test_electrovalves(&electrovalves);
    //test_callback(&communication);
    //test_electrovalves(&electrovalves);
   // test_tank(&tank);
   test_charriot(&chariot);
    
}

void test_charriot(chariot_t *chariot)
{
  PRINT("Charriot : Begin Test");

  chariot->init(chariot);
  PRINT("Charriot : Test deplacement");

  
  // for(int i = 0 ; i<4; i++)
  // {
  //   chariot->left(chariot);
  //   PRINT(chariot->speed);
  //   chariot->move(chariot);
  //   delay(GAME_DELAY_CHECK);
  // }
  // delay(1000);
  // for(int i = 0 ; i<8 ; i++)
  // {
  //   chariot->right(chariot);
  //   chariot->move(chariot);
  //   delay(GAME_DELAY_CHECK);
  // }
  // delay(1000);
  // PRINT("Charriot : Test stop");

  // chariot->stop(chariot);
  
  // delay(5000);
  // PRINT("Charriot : Test pour");
  // chariot->pour(chariot);

  PRINT("Charriot : Move to position 3");
  chariot->move_position(chariot,2);
  chariot->move_position(chariot,5);
  PRINT("Charriot : test END");

  pinMode(PIN_RIGHT_BUTTON,INPUT_PULLUP);
  pinMode(PIN_LEFT_BUTTON,INPUT_PULLUP);
  int current = millis();
  PRINT("Charriot : test MANUAL INPUT");
  while(1)
  {
    
    if(millis() - current  > GAME_DELAY_CHECK)
    {
        current = millis();
        if(!digitalRead(PIN_RIGHT_BUTTON) && !digitalRead(PIN_LEFT_BUTTON))
        {

        }else if (!digitalRead(PIN_RIGHT_BUTTON))
        {
            chariot->right(chariot);

        }else if (!digitalRead(PIN_LEFT_BUTTON))
        {
           chariot->left(chariot);
        }
        else
        {
            if (chariot->way == WAY_RIGHT){
                chariot->left(chariot);
            }
            else if (chariot->way == WAY_LEFT)
            {
                chariot->right(chariot);
            }
        }
        chariot->move(chariot);
        
    }

  }

}

void test_electrovalves(electrovalve_array_t *electrovalves )
{
  PRINT("ELECTROVALVE SETUP TEST");
  electrovalves->init(electrovalves);
  PRINT("ELECTROVALVE ACTIVATION TEST");
  for(int a = 0 ; a<3 ; a++)
  {
    PRINT("ELECTROVALVE OPEN TEST");
    // for( int i = 5 ; i >=0 ; i-- )
    // {
    //   electrovalves->open(&electrovalves->array[i]);
    //   delay(500);
    // }
    // PRINT("ELECTROVALVE CLOSE TEST");
    // for( int i = 0 ; i <=6 ; i++ )
    // {
    //   electrovalves->close(&electrovalves->array[i]);
    //   delay(500);
    // }
    PRINT("ELECTROVALVE OPEN-TIME TEST");
    for( int i = 0 ; i <=6 ; i++ )
    {
      electrovalves->openTime(&electrovalves->array[i],500);
      delay(1000);
    }
  }
  PRINT("ELECTROVALVE END TEST");

}

void test_callback(communication_t *communication)
{
  communication->init();
  PRINT("COMMUNICATION TEST START");

  
  communication->send_command(COMMANDE_START_GAME,STATUS_OK);

  communication->send_command(COMMANDE_RESPONSE,STATUS_ERROR);
  communication->send_command(COMMANDE_SEND_POSITION,STATUS_NONE);
  communication->send_command(COMMANDE_START_GAME,STATUS_OK);
  communication->send_command(COMMANDE_STOP_GAME,STATUS_ERROR);
  communication->send_command(COMMANDE_STATE_GLASS,STATUS_KO);

  while (1)
  {
      communication->check_message(communication);
  }
}


#endif
