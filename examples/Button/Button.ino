#include <BIoTEthernetClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;
//set pin numbers

const int ledPin = 4;         //const won't change
const int buttonPin = 7;

int buttonState = 0;
bool currentState = false;

void setup() {

  Serial.begin(9600);

  client.begin(ip, mac);

  Serial.println("connecting...");

  if (client.connect(server, port, token)) {

    Serial.println("connected");
  }
    pinMode(ledPin, OUTPUT);    //initialize the LED pin as an output
    pinMode(buttonPin, INPUT);  //initialize the pushbutton pin as an output
  

  }
void loop() {
  if (client.available()) {
    String message = client.readString();
  }

  buttonState = digitalRead(buttonPin); //read the state of the pushbutton value

  if (buttonState == HIGH) {            //check if the pushbutton is pressed
    //if it is, the buttonState is HIGH
    digitalWrite(ledPin, HIGH);        //turn LED on
  }

    if (currentState == false) {
      currentState = true;
      client.sendUpdate(1, "status", "true");
      Serial.println("LED ON +++++++");
    }



  
  else {
    digitalWrite(ledPin, LOW);

    if (currentState == true) {
      currentState = false;
      client.sendUpdate(1, "status", "false");
     
      Serial.println("LED OFF -------");
    }
  }

}
