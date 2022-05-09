#include <Arduino.h>
#include <HCSR04.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#define DHTTYPE DHT22 // DHT 22 (AM2302)
#define DHTPIN 2

DHT_Unified dht(DHTPIN, DHTTYPE);
UltraSonicDistanceSensor distanceSensor(13, 12); // Initialize sensor that uses digital pins 13 and 12.

void setup()
{
  Serial.begin(9600); // We initialize serial connection so that we could print values from sensor.
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  // dht.humidity().getSensor(&sensor);
  // delayMS = sensor.min_delay / 500;
}

void loop()
{
  // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
  sensors_event_t event;
  double temp;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature))
  {
    Serial.println(F("Error reading temperature!"));
  }
  else
  {
    temp = event.temperature;
    Serial.print(F("Temperature: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }
  Serial.print("Udaljenost je: ");
  Serial.println(distanceSensor.measureDistanceCm(temp));
  delay(2000);
}