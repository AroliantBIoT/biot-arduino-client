#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

const int ledPin = 6;   //the number of the LED pin
const int ldrPin = A0;  //the number of the LDR pin
int ldrStatus = 0;


void setup() {

  Serial.begin(9600);
  client.begin(ip, mac);
  Serial.println("connecting...");
  client.connect(server, port, token);
  Serial.println("connected");
  pinMode(ledPin, OUTPUT);  //initialize the LED pin as an output
  pinMode(ldrPin, INPUT);   //initialize the LDR pin as an input
}

void loop() {
  if (client.connected()) {
   

  ldrStatus = analogRead(ldrPin);   //read the status of the LDR value

  //check if the LDR status is <= 300
  //if it is, the LED is HIGH

  if (ldrStatus <= 300) {

    digitalWrite(ledPin, HIGH);               //turn LED on

    client.sendUpdate(1, "ldr", "true");

    Serial.println("LDR is DARK, LED is ON");

  }

  else {

    digitalWrite(ledPin, LOW);          //turn LED off

    client.sendUpdate(1, "ldr", "false");
    Serial.println("*****");
  }

  }

  delay(2000);
  client.run(server,port,token);
}


