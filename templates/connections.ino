#include <DHT.h>

// Define the pin for DHT11 data pin and soil moisture sensor
#define DHTPIN 5         // GPIO5 is used for DHT11 data pin
#define MOISTUREPIN 34   // GPIO34 for soil moisture sensor (analog)

#define DHTTYPE DHT11    // DHT 11 sensor

// Create an instance of the DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);
  Serial.println("DHT11 and Soil Moisture Sensor Test");

  // Initialize the DHT11 sensor
