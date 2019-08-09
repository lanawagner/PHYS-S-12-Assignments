
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
float sensorAveOne = 0;
float sensorAveTwo = 0;
void setup() {
  Serial.begin(115200);
  Serial.println(F("RF24example:  Simple tx"));
  radio.begin();

 // Set the PA Level low to prevent power supply related issues since this is a
 // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);
  
  // Open a writing and reading pipe on each radio, with opposite addresses

  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1,addresses[1]);
 
}

void loop() {

  long int sumOne = 0;

  for (int i=1; i<N+1; i++){
  int sensorValueOne = analogRead(A1);
  sumOne = sumOne + sensorValueOne;
  }

  sensorAveOne = (float)sumOne/(float)N;

  long int sumTwo = 0;

  for (int i=1; i<N+1; i++){
  int sensorValueTwo = analogRead(A4);
  sumTwo = sumTwo + sensorValueTwo;
  }

  sensorAveTwo = (float)sumTwo/(float)N;
  
// Try again 1s later

//data comes in here:


if(sensorAveOne > 0 && sensorAveOne <= 5 && sensorAveTwo > 0 && sensorAveTwo <= 5){
  //FORWARDS
  data = 1;
}
else if(sensorAveOne > 0 && sensorAveOne <= 5){
  //turn LEFT
  data = 2;
}
else if(sensorAveTwo > 0 && sensorAveTwo <= 5){
  //turn RIGHT
  data = 3;
}
else if(sensorAveTwo  > 5 && sensorAveTwo <= 450 && sensorAveOne > 5 && sensorAveOne <= 450){
  //backwards
  data = 4;
}
else {
  //stop
  data = 0;
}
Serial.print("A1: ");
Serial.println(sensorAveOne);
Serial.print("A4: ");
Serial.println(sensorAveTwo);


Serial.println("Now sending");

  
                           
   if (!radio.write( &data, 1 )){
     Serial.println(F("failed"));
   }
   radio.write(&data, 1);
        
  
Serial.print("Sent ");
Serial.println(data);

   //data ++;
delay(1000);

} // loop end

