// ################
// ### Includes ###
// ################
#include <Arduino.h>
#include <EEPROM.h>

// ###################
// ### Description ###
// ###################

// *****************************************
// *** Program the internal flash        ***
// *** We can program the first 64 bytes ***
// *****************************************

// ############
// ### PINS ###
// ############
// UART CONNECTION
#define UART2_RX 16
#define UART2_TX 17

// #################
// ### CONSTANTS ###
// #################
#define EEPROM_SIZE 64 // We retrieve 64 bytes from flash

// #############
// ### TYPES ###
// #############
enum t_FSM
{
  e_ASK_ADDRESS,
  e_GET_ADDRESS,
  e_ASK_SIZE,
  e_GET_SIZE,
  e_ASK_VALUE,
  e_GET_VALUE,
  e_PROGRAM,
  e_SHOW
};

// #################
// ### VARIABLES ###
// #################
char str[20];
int addr = 0;
int size = 0;
String value;
t_FSM FSM = e_ASK_ADDRESS;

// ###############
// ### OBJECTS ###
// ###############

// #################
// ### FUNCTIONS ###
// #################

// #############
// ### SETUP ###
// #############

void setup()
{

  Serial2.begin(115200, SERIAL_8N1, UART2_RX, UART2_TX);
  Serial2.println(F("Writing into the flash"));

  FSM = e_ASK_ADDRESS;

  EEPROM.begin(EEPROM_SIZE);

  // replace values in byte-array cache with modified data
  // no changes made to flash, all in local byte-array cache


  //EEPROM.get(addr,str);

  //Serial2.println(str);
}

// ############
// ### LOOP ###
// ############

void loop()
{

  String valueRead;
      int a = 109;

  switch (FSM)
  {

  case e_ASK_ADDRESS:
    Serial2.println(F("ENTER ADDRESS: "));
    FSM = e_GET_ADDRESS;
    break;

  case e_GET_ADDRESS:
    while (Serial2.available())
    {

      valueRead = Serial2.readString(); // read the incoming data as string
      addr = valueRead.toInt();
      Serial2.println(addr);
      Serial2.println(F("ENTER SIZE: "));
      FSM = e_ASK_SIZE;
    }
    break;

  case e_ASK_SIZE:
    FSM = e_GET_SIZE;
    break;

  case e_GET_SIZE:
    while (Serial2.available())
    {

      valueRead = Serial2.readString(); // read the incoming data as string
      size = valueRead.toInt();
      Serial2.println(size);
      Serial2.println(F("ENTER VALUE: "));
      FSM = e_ASK_VALUE;
    }
    break;

  case e_ASK_VALUE:
    FSM = e_GET_VALUE;
    break;

  case e_GET_VALUE:
    while (Serial2.available())
    {

      value = Serial2.readString(); // read the incoming data as string
      value.trim();
      Serial2.println(value);
      FSM = e_PROGRAM;
    }
    break;

  case e_PROGRAM:
    FSM = e_ASK_ADDRESS;
      Serial2.println(F(""));
      Serial2.println(F("Value to program:"));
      Serial2.print(F("\tADDRESS : "));
      Serial2.println(addr);
      Serial2.print(F("\tSIZE : "));
      Serial2.println(size);
      Serial2.print(F("\tVALUE : "));
      Serial2.println(value);
      strcpy(str,value.c_str());
      EEPROM.put(addr,str);
      EEPROM.commit();
      FSM = e_SHOW;
    break;

  case e_SHOW:
    FSM = e_ASK_ADDRESS;
      Serial2.println(F(""));
      Serial2.println(F("ADDRESS MAP"));
      for (unsigned int i = 0; i < EEPROM_SIZE -1; i++)
      {
      Serial2.print(F("\tADDRESS["));
      Serial2.print(i);
      Serial2.print(F("]: "));
      EEPROM.get(i,str);
      Serial2.println(str);
      }
    break;

  }
}