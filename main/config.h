#ifndef CONFIG_H
#define CONFIG_H

#ifdef DEBUG
#define PRINT(message) Serial.println("Debug: "+((String)message))
#else
#define PRINT(message) 0
#endif


///ELECTROVANNE
#define OPEN HIGH
#define CLOSE LOW
#define PIN_ELECTROVALVE_0 13
#define PIN_ELECTROVALVE_1 12
#define PIN_ELECTROVALVE_2 11
#define PIN_ELECTROVALVE_3 10
#define PIN_ELECTROVALVE_4 9
#define PIN_ELECTROVALVE_5 8
#define ELECTROVALVE_SIZE 6

///CHARRIOT


///COMMUNICATION
#define BAUDRATES 9600
#define BUFFERSIZE 256
#define TIMEOUT_SERIAL 100
#define END_COMMAND_CHAR '}'
#endif