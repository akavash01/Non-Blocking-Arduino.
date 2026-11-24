// Level 2: Non-blocking sensor and output
// Board: Arduino Uno
// Sensor: photoresistor module AO -> A0
// LED: D9 -> 220 ohm resistor -> LED anode; LED cathode -> GND

const byte SENSOR_PIN = A0;
const byte LED_PIN = 9;

const int LIGHT_THRESHOLD = 500;

// Two independent task rates.
const unsigned long SENSOR_INTERVAL_MS = 100;   // 10 times per second
const unsigned long REPORT_INTERVAL_MS = 1000;  // once per second

unsigned long lastSensorTime = 0;
unsigned long lastReportTime = 0;

int latestSensorValue = 0;
bool ledIsOn = false;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // millis() is driven by the Arduino core's hardware timer.
  // Subtraction-based checks remain safe when millis() rolls over.
  const unsigned long now = millis();

  // Task 1: sample the light sensor and update the LED every 100 ms.
  if (now - lastSensorTime >= SENSOR_INTERVAL_MS) {
    lastSensorTime = now;

    latestSensorValue = analogRead(SENSOR_PIN);
    ledIsOn = (latestSensorValue < LIGHT_THRESHOLD);
    digitalWrite(LED_PIN, ledIsOn ? HIGH : LOW);
  }

  // Task 2: report the most recent reading every 1000 ms.
  if (now - lastReportTime >= REPORT_INTERVAL_MS) {
    lastReportTime = now;

    Serial.print("Light level: ");
    Serial.print(latestSensorValue);
    Serial.print(" | LED: ");
    Serial.println(ledIsOn ? "ON" : "OFF");
  }

  // No delay(): loop() stays available to check both schedules.
}
