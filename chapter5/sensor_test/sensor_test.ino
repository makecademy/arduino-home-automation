// Sketch to test the current sensor

// Define current sensor pin
#define CURRENT_SENSOR A0

// Define measurement variables
float amplitude_current;
float effective_value;
float effective_voltage = 230; // Set voltage to 230V (Europe) or 110V (US)
float effective_power;
float zero_sensor;
                                         
void setup(void)
{
  // Init serial
  Serial.begin(115200);
  
  // Calibrate sensor with null current
  zero_sensor = getSensorValue();
  Serial.print("Zero point sensor: ");
  Serial.println(zero_sensor);
  Serial.println("");
  
}
  
void loop(void)
{
  
  // Perform power measurement
  float sensor_value = getSensorValue();
  Serial.print("Sensor value: ");
  Serial.println(sensor_value);
    
  // Convert to current
  amplitude_current=(float)(sensor_value-zero_sensor)/1024*5/185*1000000;
  effective_value=amplitude_current/1.414;
  
  // Plot data
  Serial.println("Current amplitude (in mA): ");
  Serial.println(amplitude_current,1);
  Serial.println("Current effective value (in mA)");
  Serial.println(effective_value,1);
  Serial.println("Effective power (in W): ");
  Serial.println(abs(effective_value*effective_voltage/1000),1);
  Serial.println("");
  
  // Poll every 50ms
  delay(500);
  
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
