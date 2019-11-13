
// REQUREMENTS: (MAY VARY) ///////////////////////////////////////////////////////////////////////////

  // PERIPHERALS: 
    // - i2c bus (ir remote temperature sensor)
    // - SPI bus (thermocouple contact controller)
    // - bluetooth (for wireless communication)
    // - Serial(debugging purposes)

  // FUNCTIONALITY:

    // PID controller (necessary to control accuerately the plate temperature).


// LIBRARIES ////////////////////////////////////////////////////////////////////////////////////////

// GLOBAL //
// libraries that are globally installed in the computer (mostly included with the language)
#include <Arduino.h>
#include "Adafruit_MLX90614.h"
// LOCAL //
// this libraries are the ones at the lib folder, which are downloaded from github and so on

// CUSTOM //
// custom created libraries


// GLOBAL VARIABLE DECLARATION ///////////////////////////////////////////////////////////////////////

const unsigned char SDA_PIN = 25;                       // pins where the i2c bus will be connected
const unsigned char SCL_PIN = 26;

Adafruit_MLX90614 irThermometer = Adafruit_MLX90614(MLX90614_I2CADDR);    // creating object ir thermometer (input device i2c addr.)

double temp;                                            // variable to store readed temperature value

// FUNCTION DECLARATION //////////////////////////////////////////////////////////////////////////////
// here we define our functions, so they can be used from the beginning of the code.


// INTERRUPTS IF NEEDED //////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                                 // starts serial communication
  Wire.begin(SDA_PIN,SCL_PIN);                          // starts I2C communication 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LOOP STARTED");                       // basic debugging print to ensure setup is finished.
  temp = irThermometer.readObjectTempC();                     // reads object temperature in ºC.
  Serial.println(temp);
  delay(100);
}


// FUNCTION IMPLEMENTATION //////////////////////////////////////////////////////////////////////////
// here we IMPLEMENT the body of our functions