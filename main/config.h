#ifndef CONFIG_H
#define CONFIG_H

#define DEBUG

#ifdef DEBUG
#define PRINT(message) Serial.println("Debug: "+((String)message))
#else
#define PRINT(message) 0
#endif


///ELECTROVANNE
#define PIN_ELECTROVALVE_0 1
#define PIN_ELECTROVALVE_1 1
#define PIN_ELECTROVALVE_2 1
#define PIN_ELECTROVALVE_3 1
#define PIN_ELECTROVALVE_4 1
#define PIN_ELECTROVALVE_5 1
#define ELECTROVALVE_SIZE 6

///CHARRIOT


///COMMUNICATION
#define BAUDRATES 9600
#define BUFFERSIZE 256
#define TIMEOUT_SERIAL 100
#define END_COMMAND_CHAR '}'
#endif