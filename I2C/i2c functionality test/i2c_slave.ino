//Include the Wire library for i2c
#include <Wire.h>

const int ledPin = 13;

void setup() {
 // Join I2Cbus as slave with address 8
 Wire.begin(0x8);

 //CallreceiverEvent when data received
 Wire.onReceive(receivedEvent);

 //Setup pin 13 as output  and turn LED off
 pinMode(ledPin,OUTPUT);
 digitalWrite(ledPin,LOW);

}

//Function that executes whenever  data is received from master
void receivedEvent(int howMany){
  while (Wire.available()){
    char c = Wire.read();
    digitalWrite(ledPin,c);
  }
}

void loop() {
  delay(100);

}
