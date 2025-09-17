#include "Arduino_BHY2Host.h"
Sensor temp(SENSOR_ID_TEMP);
Sensor pressure(SENSOR_ID_BARO);
Sensor gas(SENSOR_ID_GAS);
    
void setup() { 
  Serial.begin(115200);
  BHY2Host.begin();
  temp.begin();
  pressure.begin();
  gas.begin();
}

void loop() {
  if (Serial.available()) {
    // Read the string from the computer to find number of readings to take
    String numberofReadingsString = Serial.readStringUntil('\n');
    int numberofReadings = numberofReadingsString.toInt();

      // If prompted, collect some data
    unsigned long dataTime = 0;
    unsigned long startTime = millis();

    for (int n = 0; n < numberofReadings; n++) {  
      BHY2Host.update();    // Update the sensor readings 

      // Collect the data
      dataTime = millis() - startTime;
      float dataTemp = temp.value();
      float dataP = pressure.value();
      float dataG = gas.value();

      // Write the data to the serial port
      Serial.print(dataTime);
      Serial.print(',');
      Serial.print(dataTemp);
      Serial.print(',');
      Serial.print(dataP);
      Serial.print(',');
      Serial.print(dataG);
      Serial.print('\n');
    } // ends for loop()
  } // ends if(Serial.available()) 
} // end loop()
