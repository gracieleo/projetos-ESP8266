
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>    


ThingerESP8266 thing("xxxxx", "xxxx", "xxxxx");  // thinger.io( username,device name,device credentials )
int pushPin = 14;                               //the digital pin to the PIR sensor's output
int ledPin = 4;
int val = 0;                                    //variable for reading pin status


void setup() {

  pinMode(ledPin, OUTPUT);                            // declare LED  as output
  pinMode(pushPin, INPUT_PULLUP);                     //declare push button as input
  Serial.begin(9600);
  
  //connecting to WiFi
  thing.add_wifi("your_ssid", "your_password");       //SSID & password for mobile hotspot
  Serial.println("entering the gates");
}

void loop() {
  
  val = digitalRead(pushPin);
  Serial.println(val);                              //read input value
  if (val == LOW) {                                 //checks if the input is High (button released)
    digitalWrite(ledPin, HIGH);                     //turn LED OFF
    delay(1000);
    digitalWrite(ledPin, LOW);

    thing.handle();
    thing.call_endpoint("EmailService");
    delay(5000);
    //digitalWrite(inPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);  //turn LED ON
  }

}
