
/*
  Simple sketch for nRF24L01+ radios  Receive side.

  Updated: Dec 2014 by TMRh20. Simplified Mar 2019 RMH.
*/

#include <SPI.h>
#include "RF24.h"

int val = 0;
int i = 0;
/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7, 8);


byte addresses[][6] = {"1Lana", "2Lana"};

byte rec_data;

void setup() {

  Serial.begin(115200);
  Serial.println(F("RF24example:  simple receive"));

  radio.begin();

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);


  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);


  // Start the radio listening for data
  radio.startListening();
  attachInterrupt(0, check_radio, LOW);
}

void loop() {

  //switch case for movements depending on what it receives

  if (rec_data == 1) {
    //Forwards
    analogWrite(3, 255);
    analogWrite(5, 0);
    analogWrite(6, 255);
    analogWrite(9, 0);


  }
  else if (rec_data == 2) {
    //Turn Left
    analogWrite(3, 255);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);


  }
  else if (rec_data == 3) {
    //Turn Right
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 255);
    analogWrite(9, 0);

  }
  else if (rec_data == 4) {
    //backwards
    analogWrite(3, 0);
    analogWrite(5, 255);
    analogWrite(6, 0);
    analogWrite(9, 255);
  }
  else {
    //Stop
    analogWrite(3, 0);
    analogWrite(5, 0);
    analogWrite(6, 0);
    analogWrite(9, 0);

  }








} // Loop

void check_radio(void) {
  while (radio.available()) {                                   // While there is data ready
    radio.read( &rec_data, 1 );             // Get the payload
  }
  Serial.print("received ");
  Serial.println(rec_data);
}

