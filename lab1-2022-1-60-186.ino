// Define the analog pin where the sensor is connected
const int sensorPin = A0;

// Calibrated min and max raw sensor values
const int minDryValue = 200;        // Example dry sensor reading
const int maxSubmergedValue = 800;  // Example fully submerged sensor reading

// Define water level thresholds
const int LOW_LEVEL = 25;
const int MEDIUM_LEVEL = 75;
const int HIGH_LEVEL = 95;

// Variables to store previous water level and last alarm triggered
int previousLevel = -1;
int lastAlarm = 0;  // 0 = none, 1 = low, 2 = medium, 3 = high

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Read the raw sensor value
  int rawSensorValue = analogRead(sensorPin);

  // Map raw value to percentage 0-100%
  int percentage = map(rawSensorValue, minDryValue, maxSubmergedValue, 0, 100);
  percentage = constrain(percentage, 0, 100);

  // Calculate rate of change
  int rateOfChange = 0;
  if (previousLevel != -1) {
    rateOfChange = percentage - previousLevel;
  }
  previousLevel = percentage;

  // Print to Serial Plotter: water level % and rate of change
  Serial.print(percentage);
  Serial.print(",");
  Serial.println(rateOfChange);

  // Check thresholds and print alarm only when crossing into new threshold
  if (percentage >= HIGH_LEVEL && lastAlarm != 3) {
    Serial.println("ALARM: HIGH WATER LEVEL reached!");
    lastAlarm = 3;
  }
  else if (percentage >= MEDIUM_LEVEL && percentage < HIGH_LEVEL && lastAlarm != 2) {
    Serial.println("ALERT: MEDIUM WATER LEVEL reached.");
    lastAlarm = 2;
  }
  else if (percentage >= LOW_LEVEL && percentage < MEDIUM_LEVEL && lastAlarm != 1) {
    Serial.println("Warning: LOW WATER LEVEL reached.");
    lastAlarm = 1;
  }
  else if (percentage < LOW_LEVEL && lastAlarm != 0) {
    Serial.println("Water level is below LOW LEVEL threshold.");
    lastAlarm = 0;
  }

  delay(100);
}