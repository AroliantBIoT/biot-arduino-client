#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

const int ledPin = 2;       
const int buttonPin = 4;

int buttonState = 0;
bool currentState = false;

void setup() {

  Serial.begin(9600);

  client.begin(ip, mac);

  Serial.println("connecting...");

  if (client.connect(server, port, token)) {

    Serial.println("connected");
    pinMode(ledPin, OUTPUT);    //initialize the LED pin as an output
    pinMode(buttonPin, INPUT);  //initialize the pushbutton pin as an output
  }
}

void loop() {
  if (client.available()) {
    String message = client.readString();
  }

  buttonState = digitalRead(buttonPin); 
  if (buttonState == HIGH) {            
    //if it is, the buttonState is HIGH
    digitalWrite(ledPin, HIGH);        
    

    if (currentState == false) {
      currentState = true;
      client.sendUpdate(1, "status", "true");
      Serial.println("LED ON");
    }


  }
  else {
    digitalWrite(ledPin, LOW);

    if (currentState == true) {
      currentState = false;
      client.sendUpdate(1, "status", "false");
     
      Serial.println("LED OFF");
    }
  }

}
