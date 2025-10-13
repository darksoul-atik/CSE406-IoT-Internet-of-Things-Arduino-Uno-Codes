#include <DHT.h>

// Water level sensor pin
const int sensorPin = A0;  // NodeMCU ADC pin

// DHT11 sensor settings
#define DHTPIN 2        // GPIO2 (D4 on NodeMCU)
#define DHTTYPE DHT11   // DHT11 sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 and Water Level Sensor Test!");
  dht.begin();
}

void loop() {
  // Wait 2 seconds between readings (DHT11 sensor timing)
  delay(2000);

  // Read water level sensor
  int sensorValue = analogRead(sensorPin);

  // Read humidity and temperature from DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Check if DHT11 reads failed
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Print water level and DHT11 readings
    Serial.print("Raw Water Level Sensor Value: ");
    Serial.print(sensorValue);
    Serial.print(" | Humidity: ");
    Serial.print(h);
    Serial.print("%");
    Serial.print(" | Temperature: ");
    Serial.print(t);
    Serial.println(" °C");
  }
}


