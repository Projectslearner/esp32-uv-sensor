/*
   Project name: ESP32 UV Sensor (VEML6070)
   Modified Date: 25-06-2024
   Code by: Projectslearner
   Website: https://projectslearner.com/learn/esp32-uv-sensor-veml6070
*/

#include <Wire.h>

// VEML6070 I2C address (0x10 or 0x38)
#define VEML6070_ADDR 0x10

void setup() {
  Serial.begin(9600); // Initialize serial communication
  Wire.begin(); // Initialize I2C communication

  // Configure the UV sensor
  configureVEML6070();
}

void loop() {
  // Read UV index from the sensor
  float uvIndex = readUVIndex();

  // Print UV index to Serial Monitor
  Serial.print("UV Index: ");
  Serial.println(uvIndex);

  delay(1000); // Delay before next reading
}

void configureVEML6070() {
  // Set configuration register (0x02): Dynamic, Integration time = 1/2T
  Wire.beginTransmission(VEML6070_ADDR);
  Wire.write(0x02);
  Wire.write(0x11); // Enable and set integration time to 1/2T (default)
  Wire.endTransmission();
}

float readUVIndex() {
  // Read UV index from the sensor (two bytes)
  Wire.requestFrom(VEML6070_ADDR, 2);
  if (Wire.available() == 2) {
    uint16_t uvRaw = Wire.read(); // LSB
    uvRaw |= Wire.read() << 8; // MSB

    // Convert raw sensor value to UV index
    float uvIndex = uvRaw * 0.1;

    return uvIndex;
  } else {
    Serial.println("Error: Unable to read UV index from sensor.");
    return -1.0; // Return negative value if there's an error
  }
}
