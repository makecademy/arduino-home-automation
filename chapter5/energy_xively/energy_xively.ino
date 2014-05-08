// Sketch to send power consumption data to Xively

// Libraries
#include <Adafruit_CC3000.h>
#include <SPI.h>

// Define CC3000 chip pins
#define ADAFRUIT_CC3000_IRQ   3
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

// Define current sensor pin
#define CURRENT_SENSOR A0

// Define measurement variables
float amplitude_current;
float effective_value;
float effective_voltage = 230; // Set voltage to 230V (Europe) or 110V (US)
float effective_power;
float zero_sensor;

// Create CC3000 instances
Adafruit_CC3000 cc3000 = Adafruit_CC3000(ADAFRUIT_CC3000_CS, ADAFRUIT_CC3000_IRQ, ADAFRUIT_CC3000_VBAT,
                                         SPI_CLOCK_DIV2); // you can change this clock speed

// WLAN parameters
#define WLAN_SSID       "yourSSID"
#define WLAN_PASS       "yourPassword"
// Security can be WLAN_SEC_UNSEC, WLAN_SEC_WEP, WLAN_SEC_WPA or WLAN_SEC_WPA2
#define WLAN_SECURITY   WLAN_SEC_WPA2

// Xively parameters
#define WEBSITE  "api.xively.com"
#define API_key  "yourAPIKey"
#define feedID  "yourFeedID"

uint32_t ip;

void setup(void)
{
  // Initialize Serial
  Serial.begin(115200);
  
  // Calibrate sensor with null current
  zero_sensor = getSensorValue();
  Serial.print("Zero point sensor: ");
  Serial.println(zero_sensor);
  Serial.println("");
  
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
  uint32_t ip = cc3000.IP2U32(216,52,233,120);
  cc3000.printIPdotsRev(ip);

  // Perform power measurement
  float sensor_value = getSensorValue();
  Serial.print("Sensor value: ");
  Serial.println(sensor_value);
    
  // Convert to current
  amplitude_current=(float)(sensor_value-zero_sensor)/1024*5/185*1000000;
  effective_value=amplitude_current/1.414;
  effective_power = abs(effective_value*effective_voltage/1000);
        
  // Prepare JSON for Xively & get length
  int length = 0;
  String data = "";
  data = data + "\n" + "{\"version\":\"1.0.0\",\"datastreams\" : [ {\"id\" : \"Current\",\"current_value\" : \"" + String((int)effective_value) + "\"}," + "{\"id\" : \"Power\",\"current_value\" : \"" + String((int)effective_power) + "\"}]}";
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

// Get the reading from the current sensor
float getSensorValue()
{
  int sensorValue;
  float avgSensor = 0;
  int nb_measurements = 100;
  for (int i = 0; i < nb_measurements; i++) {
    sensorValue = analogRead(CURRENT_SENSOR);
    avgSensor = avgSensor + float(sensorValue);
  }	  
  avgSensor = avgSensor/float(nb_measurements);
  return avgSensor;
}
