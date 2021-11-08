/**
 * File name: 			  main.cpp
 * File description:	This file contains all necessary resources to mock the
 *                    LSM303DHLC magnetic field sensor using I2C.
 *
 * Author name:			Mauro Chiozzi
 *
 * Reference: [1] - https://pdf1.alldatasheet.com/datasheet-pdf/view/505234/STMICROELECTRONICS/LSM303DLHC.html
 *
 */

#include <Wire.h>
#include <Arduino.h>

// --------------------------------------------------------------------------------------------- //
// If debug is set to true, system will send thru default serial port messages
// regarding status and informations
#define DEBUG true

// Auxiliar Union... Maybe it will not be required... Lets see
union union_i16_ui8
{
  uint8_t ui8[6];
  int16_t i16[3];
};

union_i16_ui8 magnetic_fields;

// --------------------------------------------------------------------------------------------- //
// I2C

/**
 * Define LSM303DLHC I2C address
 *
 * Reference: [1] section 5.1.3, p21
 */
#define LSM303DLHC_MOCK_ADD (0x1E)

/**
 * Stores request value from master
 */
uint8_t ui8_request_value;

/**
 * Method name: 			    initialize
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void initialize();

/**
 * Method name: 			    initializeI2C
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void initializeI2C();

/**
 * Method name: 			    initializeDebug
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void initializeDebug();

/**
 * Method name: 			    routine
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void routine();

// --------------------------------------------------------------------------------------------- //

/**
 * Method name: 			    onRequest
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void onRequest();

/**
 * Method name: 			    onReceive
 * Method description:
 *
 * Input params:			    ui8_size
 *
 * Output params:			    None
 */
void onReceive(int size);

/**
 * Method name: 			    consumeRequest
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
void consumeRequest();

/**
 * Method name: 			    writeTwoBytes
 * Method description:
 *
 * Input params:			    i16_bytes_to_send
 *
 * Output params:			    None
 */
void writeTwoBytes(int16_t i16_bytes_to_send);

/**
 * Method name: 			    main
 * Method description:
 *
 * Input params:			    None
 *
 * Output params:			    None
 */
int main()
{
  initialize();

  while (true)
  {
    routine();
  }
}

void initialize()
{
  init();
  initializeI2C();
  initializeDebug();

  magnetic_fields.i16[0] = 1000;
  magnetic_fields.i16[1] = 1000;
  magnetic_fields.i16[2] = 500;
}

void routine()
{
#if DEBUG
  Serial.println("Hello");
  delay(500);
#endif
}

void initializeI2C()
{
  Wire.begin(LSM303DLHC_MOCK_ADD);
  Wire.onReceive(onReceive);
  Wire.onRequest(onRequest);
}

void initializeDebug()
{
#if DEBUG
  Serial.begin(115200);
  Serial.println("Debugging...");
#endif
}

void onReceive(int size)
{
  if (Wire.available())
  {
    ui8_request_value = Wire.read();

#if DEBUG
    Serial.print("Request received: ");
    Serial.println(ui8_request_value);
#endif
  }
}

void onRequest()
{
  if (ui8_request_value == 0x00)
  {
#if DEBUG
    Serial.print("Request received: ");
    Serial.println(ui8_request_value);
#endif

    consumeRequest();
  }
  else if (ui8_request_value == 0x01)
  {
#if DEBUG
    Serial.print("Request received: ");
    Serial.println(ui8_request_value);
#endif

    consumeRequest();
  }
  else if (ui8_request_value == 0x02)
  {
#if DEBUG
    Serial.print("Request received: ");
    Serial.println(ui8_request_value);
#endif

    consumeRequest();
  }
  else if (ui8_request_value == 0x03)
  {
#if DEBUG
    Serial.print("Request received: ");
    Serial.println(ui8_request_value);
#endif

    writeTwoBytes(magnetic_fields.i16[0]);
    writeTwoBytes(magnetic_fields.i16[1]);
    writeTwoBytes(magnetic_fields.i16[2]);

    consumeRequest();
  }
}

void consumeRequest()
{
  ui8_request_value = 0x00;
}

void writeTwoBytes(int16_t i16_bytes_to_send)
{
  Wire.write((i16_bytes_to_send >> 8) & 0xFF);
  Wire.write((i16_bytes_to_send)&0xFF);
}
