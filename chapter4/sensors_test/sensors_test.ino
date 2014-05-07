// Test sketch for the DHT11 & photocell sensors

// Include required libraries
#include "DHT.h"

// Variables
int lightLevel;
float humidity;
float temperature;

// DHT11 sensor pins
#define DHTPIN 7 
#define DHTTYPE DHT11

// DHT instance
DHT dht(DHTPIN, DHTTYPE);
                                         
void setup(void)
{
 
  // Initialize DHT sensor
  dht.begin();
  
  // Init serial
  Serial.begin(115200);
  
}
  
void loop(void)
{
  
    // Measure the humidity
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    int lightLevel = analogRead(A0);
    
    // Print measurements
    Serial.print("Temperature: ");
    Serial.println(temperature);
    Serial.print("Humidity: ");
    Serial.println(humidity);
    Serial.print("Light level: ");
    Serial.println(lightLevel);
    Serial.println("");
    
    // Repeat every 500 ms
    delay(500);
  
}
