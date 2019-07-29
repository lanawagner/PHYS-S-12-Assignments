
/*
* Simple sketch for nRF24L01+ radios.  Transmit side.
* 
* Updated: Dec 2014 by TMRh20. Simplified Mar 2019 RMH.
*/

#include <SPI.h>
#include "RF24.h"

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);

byte addresses[][6] = {"1Lana","2Lana"};
byte data;

int N=100;
float sensorAve = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24example:  Simple tx"));
  radio.begin();

 // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_LOW);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
 
}

void loop() {

  long int sum = 0;

  for (int i=1; i<N+1; i++){
  int sensorValue = analogRead(A2);
  sum = sum + sensorValue;
  }

  sensorAve = (float)sum/(float)N;
  
Serial.println("Now sending");

  
                           
   if (!radio.write( &data, 1 )){
     Serial.println(F("failed"));
   }
   radio.write(&data, 1);
        
  
Serial.print("Sent ");
Serial.println(data);
   
// Try again 1s later

//data comes in here:
if(sensorAve > 0 && sensorAve <= 5){
  data = 1;
}
else if(sensorAve > 5 && sensorAve <= 400){
  data = 2;
}
else if(sensorAve > 400){
  data = 3;
}
Serial.println(sensorAve);

//data ++;
delay(1000);

} // loop end

