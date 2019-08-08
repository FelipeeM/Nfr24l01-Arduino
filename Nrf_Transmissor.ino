#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int Signal = 2;
boolean button_state = 0;
void setup() {
pinMode(Signal, OUTPUT);
   digitalWrite(Signal, HIGH);
radio.begin();                  //Starting the Wireless communication
radio.openWritingPipe(address); //Setting the address where we will send the data
radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
radio.stopListening();          //This sets the module as transmitter
Serial.begin(9600);

}
void loop()
{
button_state = digitalRead(Signal);
if(digitalRead(Signal) == 0)
{

  Serial.print("HIGH");
  Serial.print("\n");
const char text[] = "Your Button State is HIGH";
radio.write(&text, sizeof(text));   //Sending the message to receiver
}
else
{
  
  Serial.print("LOW");
  Serial.print("\n");
const char text[] = "Your Button State is LOW";
radio.write(&text, sizeof(text));                  //Sending the message to receiver 
}
radio.write(&button_state, sizeof(button_state));  //Sending the message to receiver 
delay(1000);
}
