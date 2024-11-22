#include <DHT.h>

// Define DHT sensor type and pin
#define DHTPIN 2       // DHT sensor connected to digital pin 2
#define DHTTYPE DHT11  // Change to DHT22 if you're using it
DHT dht(DHTPIN, DHTTYPE);

// Define Soil Moisture sensor pin
#define SOIL_MOISTURE_PIN A0 // Analog pin A0

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  dht.begin();         // Initialize DHT sensor
  pinMode(SOIL_MOISTURE_PIN, INPUT); // Configure Soil Moisture pin
  Serial.println("DHT and Soil Moisture Sensor Test!");
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius by default

  // Read Soil Moisture Sensor value
  int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);

  // Convert soil moisture value to percentage (optional calibration needed)
  int soilMoisturePercent = map(soilMoistureValue, 1023, 0, 0, 100);

  // Display readings
  Serial.println("---------- Sensor Readings ----------");
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
   
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  Serial.print("Soil Moisture (Raw): ");
  Serial.println(soilMoistureValue);

  Serial.print("Soil Moisture (%): ");
  Serial.println(soilMoisturePercent);

  // Wait for 2 seconds before next reading
  delay(2000);
}
