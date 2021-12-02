#include <cactus_io_AM2302.h>

#define AM2302_PIN  2
AM2302 dht(AM2302_PIN);


void setup() {
  Serial.begin(9600); 
  dht.begin();
}

void loop(){
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  dht.readHumidity();
  dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.humidity) || isnan(dht.temperature_C)) {
    Serial.println("AM2302 sensor read failure!");
    return;
  }

  Serial.print(dht.humidity); Serial.print(" %\t\t");
  Serial.print(dht.temperature_C); Serial.print(" *C\t");
  Serial.print(dht.computeHeatIndex_C()); Serial.print(" *C\t");
  
  // Wait a few seconds between measurements. The AM2302 should not be read at a higher frequency of
  // about once every 2 seconds. So we add a 3 second delay to cover this.
  delay(3000);
  }
