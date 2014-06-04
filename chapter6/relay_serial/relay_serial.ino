// Serial command of the relay

// Libraries
#include <SPI.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

void setup(void)
{  
  // Start Serial
  Serial.begin(9600);

}

void loop() {  
  
  // Handle REST calls
  rest.handle(Serial);  
  
}
