#ifndef CONFIG_H
#define CONFIG_H

#ifdef DEBUG
#define PRINT(message) Serial.println("Debug: "+((String)message))
#else
#define PRINT(message) 0
#endif

///GAME
#define PIN_RIGHT_BUTTON 12
#define PIN_LEFT_BUTTON 11
#define BUTTON_SIZE 2

#define PIN_MAIN_PUMP 39
#define PIN_SENSOR_SHARP A1
#define THRESHOLD_GLASS_PRESENT 800
#define GAME_DELAY_CHECK 100
#define GAME_POSITION_CENTER 0


///ELECTROVANNE
#define OPEN HIGH
#define CLOSE LOW
#define PIN_ELECTROVALVE_0 53
#define PIN_ELECTROVALVE_1 51
#define PIN_ELECTROVALVE_2 49
#define PIN_ELECTROVALVE_3 47
#define PIN_ELECTROVALVE_4 45
#define PIN_ELECTROVALVE_5 43

#define ELECTROVALVE_SIZE 6

///CHARRIOT
#define PIN_1_MOTOR 6
#define PIN_2_MOTOR 5

#define MOTOR_SLICE_VALUE 15
// #define SLICE_DELAY_MS 50

#define MOTOR_MAX_VALUE 255
#define MOTOR_MIN_VALUE 0 
#define MOTOR_MOVE_POSITION_MULTIPLE 5

#define PIN_SERVO 3
#define SERVO_ANGLE_MIN 0
#define SERVO_ANGLE_MAX 180
#define SERVO_DELAY_MS 10

#define PIN_SENSOR_POSITION_0 22
#define PIN_SENSOR_POSITION_1 23
#define PIN_SENSOR_POSITION_2 24
#define PIN_SENSOR_POSITION_3 25
#define SENSOR_POSITION_SIZE 4
// #define DELAY_CHECK_MOVE_POSITION 200


#define POUR_TIME_MS 5000 
///COMMUNICATION
#define BAUDRATES 9600
#define BUFFERSIZE 255
#define TIMEOUT_SERIAL 100
#define END_COMMAND_CHAR '}'

///CUVE
#define PIN_TANK_SENSOR A0
#define PIN_TANK_PUMP 41
#define THRESHOLD_TANK_FULL 100
#endif