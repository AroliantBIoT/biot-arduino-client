# BIoT Arduino Client

Download this Repository and include in the project.

### Usage

Include the `BIoTEthernetClient.h` header for Ethernet Shield

```cpp
#include <BIoTEthernetClient.h>
```
Define the mac and ip adddress for your shield
```cpp
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
```
Declare server ip and port
```cpp
    byte server[] =  { 192, 168 , 100 , 10 };
    int port = 5001 ;
    String token = "12345"; //token generated from BIoT Dashboard
```
In the setup function set the baud rate to 9600 .
```cpp
void setup() {
  Serial.begin(9600);

  client.begin(ip, mac); // Start the client
  Serial.println("connecting...");

  client.connect(server, port, token); // Connect to server

}
```

In the loop function listen for events from the server


```cpp
if(client.available()){

    String message = client.readString(); //Get the message from server 

    if(client.getEventName(message) == client.EVENT_UPDATE){ // Checking if the event is an update event
      Serial.println("Update Event Received");

     Serial.print("Device ID"); Serial.println(client.getDeviceID(message));  // Parsing the device id
     Serial.print("Param"); Serial.println(client.getParamName(message));     // Parsing the parameter name
     Serial.print("Value");  Serial.println(client.getParamValue(message));   // Parsing the parameter value
      
```
### Sample Program to Listen Events from Server:

```cpp
#include <BIoTEthernetClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  client.begin(ip, mac);

  Serial.println("connecting...");

  if (client.connect(server, port, token)) {

    Serial.println("connected");

  }

}


void loop() {

  if(client.available()){

    String message = client.readString();

    if(client.getEventName(message) == client.EVENT_UPDATE){
      Serial.println("Update Event Received");

     Serial.print("Device ID"); Serial.println(client.getDeviceID(message));  
     Serial.print("Param"); Serial.println(client.getParamName(message));
     Serial.print("Value"); Serial.println(client.getParamValue(message)); 
      
    }

    
  }


}
```

### Sample Program to Send Events to Server:

```cpp
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
```
