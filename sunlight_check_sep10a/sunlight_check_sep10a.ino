#include "arduino_secrets.h"
#include "thingProperties.h"
#include <Wire.h>
#include <BH1750.h>

BH1750 light_var;


float light_value;
const float threshold_value = 1000;

void setup() {

  // Initialize serial and wait for port to open
  Serial.begin(9600);

  // Initialize the I2C bus
  Wire.begin();

  // Initialize the light sensor
  light_var.begin();

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
}

void loop() {
  
  // Update IoT Cloud
  ArduinoCloud.update();
  
    // Read the light level from the sensor
    light_value = light_var.readLightLevel();
    
    // Check if the light level is above the threshold
    if (light_value >= threshold_value && sun_value != "started")
    {
      sun_value = "started";
    }
    // Check if the light level is below the threshold
    else if (light_value < threshold_value && sun_value != "stopped") {
      sun_value = "stopped";
    }
	delay(2000);
}