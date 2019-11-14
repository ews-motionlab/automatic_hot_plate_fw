
// REQUREMENTS: (MAY VARY) ///////////////////////////////////////////////////////////////////////////

  // PERIPHERALS: 
    // - IO pin, enables and disables heater
    // - i2c bus (ir remote temperature sensor)
    // - SPI bus (thermocouple contact controller)
    // - bluetooth (for wireless communication)
    // - Serial(debugging purposes)

  // FUNCTIONALITY:

    // 1. Completely stop if a too high temperature is reached (safety feature)
    // 2. simple ON on until reaching max operating temp and OFF until below min. operating temp.
    // 3. PID controller (necessary to control accuerately the plate temperature).


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
const unsigned char HEATER_SSR_PIN = 14;                // pin to switch the heater on and off. 

const float ABSOLUTE_MAX_TEMP = 70;                     // defines the absolute maximum safe temperature.


Adafruit_MLX90614 irThermometer = Adafruit_MLX90614(MLX90614_I2CADDR);    // creating object ir thermometer (input device i2c addr.)

double temp;                                            // variable to store readed temperature value

// FUNCTION DECLARATION //////////////////////////////////////////////////////////////////////////////
// here we define our functions, so they can be used from the beginning of the code.

void initIO(void);                                      // initializes the IO pins as required.


// INTERRUPTS IF NEEDED //////////////////////////////////////////////////////////////////////////////

void setup() {
  // put your setup code here, to run once:
  initIO();                                             // initializes all required IO pins 
  Serial.begin(115200);                                 // starts serial communication
  Wire.begin(SDA_PIN,SCL_PIN);                          // starts I2C communication 
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("LOOP STARTED");                             // basic debugging print to ensure setup is finished.
  temp = irThermometer.readObjectTempC();                     // reads object temperature in ºC.
  Serial.println(temp);
  if(temp > ABSOLUTE_MAX_TEMP){                               // if we reach the maximum safe temperature, we block the system
    Serial.println("HIGHEST SAFE TEMPERATURE REACHED !!!");
    Serial.println("System is blocked and heater disconnected");
    Serial.println("Reset or switch off/on to unblock");
    while(true);                                              // blocks the system
  }
  delay(100);
}


// FUNCTION IMPLEMENTATION //////////////////////////////////////////////////////////////////////////
// here we IMPLEMENT the body of our functions

void initIO(){
  pinMode(HEATER_SSR_PIN, OUTPUT);
  digitalWrite(HEATER_SSR_PIN, LOW);
}