#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int ledpin = 7;
int buttonPin = 3;
int buttonState = 0;
bool ledState = LOW;
bool ledpinState=LOW;
void setup() {
Serial.begin(9600);
client.begin(ip, mac);
Serial.println("connecting...");
client.connect(server, port, token);
Serial.println("connected");
pinMode(ledpin, OUTPUT);
pinMode(buttonPin, INPUT);
}


void loop() {
  if (client.connected()) {
    buttonState = digitalRead(buttonPin);
  }
  if (buttonState == HIGH) {
    digitalWrite(ledpin, HIGH);
  if (ledState == false) {
      ledState = true;
      client.sendUpdate(1, "ledpin", "true");
      Serial.println("button is pressed led on");
    }
  }

  else {
    digitalWrite(ledpin, LOW);

    if (ledState == true) {
      ledState = false;
      client.sendUpdate(1, "ledpin", "false");

      Serial.println("led off");
    }
  }
  client.run(server,port,token);

}

