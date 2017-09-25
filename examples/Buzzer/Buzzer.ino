#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int buzzer = 7;
int buttonPin = 3;
int buttonState = 0;
bool currentState = LOW;
bool buzzerState=LOW;
void setup() {
Serial.begin(9600);
client.begin(ip, mac);
Serial.println("connecting...");
client.connect(server, port, token);
Serial.println("connected");
pinMode(buzzzer, OUTPUT);
pinMode(buttonPin, INPUT);
}


void loop() {
  if (client.connected()) {
    buttonState = digitalRead(buttonPin);
  }
  if (buttonState == HIGH) {
    digitalWrite(buzzer, HIGH);
  if (currentState == false) {
      currentState = true;
      client.sendUpdate(1, "buzzer", "true");
      Serial.println("buzzzz");
    }
  }

  else {
    digitalWrite(buz, LOW);

    if (currentState == true) {
      currentState = false;
      client.sendUpdate(1, "buzzer", "false");

      Serial.println("buzzzz");
    }
  }
  client.run(server,port,token);

}

