// Upload weather data to Xively

// Libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>
#include "DHT.h"

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// DHT sensor
#define DHTPIN 7
#define DHTTYPE DHT11

// Create CC3000 instances
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2); // you can change this clock speed
                                         
// DHT instance
DHT dht(DHTPIN, DHTTYPE);

// WLAN parameters
#define WLAN_SSID       "yourSSID"
#define WLAN_PASS       "yourPassword"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

// Xively parameters
#define WEBSITE  "api.xively.com"
#define API_key  "yourAPIkey"
#define feedID  "yourFeedID"

unsigned long ip;

void setup(void)
{
  // Initialize Serial
  Serial.begin(115200);
  
  // Initialize CC3000 chip
  Serial.println(F("\nInitializing..."));
  if (!cc3000.begin())
  {
    Serial.println(F("Couldn't begin()! Check your wiring?"));
    while(1);
  }
 
}

void loop(void)
{
  // Connect to WiFi network
  cc3000.connectToAP(WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println(F("Connected!"));
  
  // Wait for DHCP to complete
  Serial.println(F("Request DHCP"));
  while (!cc3000.checkDHCP())
  {
    delay(100);
  }  
  Serial.println("DHCP OK");

  // Set the website IP
  cc3000.getHostByName(WEBSITE, &ip);
  cc3000.printIPdotsRev(ip);

  // Measure data
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int lightLevel = analogRead(A0);
        
  // Prepare JSON for Xively & get length
  int length = 0;
  String data = "";
  data = data + "\n" + "{\"version\":\"1.0.0\",\"datastreams\" : [ {\"id\" : \"Temperature\",\"current_value\" : \"" + String((int)temperature) + "\"}," + "{\"id\" : \"Light\",\"current_value\" : \"" + String(lightLevel) + "\"}," + "{\"id\" : \"Humidity\",\"current_value\" : \"" + String((int)humidity) + "\"}]}";
  Serial.println(data);
  length = data.length();
  
  // Send request
  Adafruit_CC3000_Client client = cc3000.connectTCP(ip, 80);
  if (client.connected()) {
    Serial.println("Connected!");
    client.println("PUT /v2/feeds/" + String(feedID) + ".json HTTP/1.1");
    client.println("Host: api.xively.com");
    client.println("X-ApiKey: " + String(API_key));
    client.println("Content-Length: " + String(length));
    client.print("Connection: close");
    client.println();
    client.print(data);
    client.println();
  } else {
    Serial.println(F("Connection failed"));    
    return;
  }
  
  Serial.println(F("-------------------------------------"));
  while (client.connected()) {
    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }
  }
  client.close();
  Serial.println(F("-------------------------------------"));
  
  Serial.println(F("\n\nDisconnecting"));
  cc3000.disconnect();
  
  // Wait 10 seconds until next update
  delay(10000);
  
}
