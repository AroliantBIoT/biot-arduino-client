[![GitHub version](https://img.shields.io/github/release/aroliantbiot/biot-arduino-client.svg)](https://github.com/aroliantbiot/biot-arduino-client/releases/latest)
[![GitHub download](https://img.shields.io/github/downloads/aroliantbiot/biot-arduino-client/total.svg)](https://github.com/aroliantbiot/biot-arduino-client/releases/latest)
[![GitHub stars](https://img.shields.io/github/stars/aroliantbiot/biot-arduino-client.svg)](https://github.com/aroliantbiot/biot-arduino-client)
[![GitHub issues](https://img.shields.io/github/issues/aroliantbiot/biot-arduino-client.svg)](https://github.com/aroliantbiot/biot-arduino-client/issues)

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
  
if (client.available()) {

    BIoTMessage message(client.readString()); //Get the message from server 

    if (message.getEventName() == BIOT_EVENT_UPDATE &&
        message.getDeviceID() == 1 && 
        message.getParamName() == "status" ) { // Checking update event, device id & param name
      
      Serial.println("Update Event => device id : 1, param : status");
      Serial.print(message.getLog()); // Printing the message from Server
      
    }

  }

client.run(server,port,token); //Reconnecting if not connected
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

int led = 3;

void setup() {
  Serial.begin(9600);
  client.begin(ip, mac);

  Serial.println("connecting...");

  client.connect(server, port, token);

  pinMode(led, OUTPUT);

}


void loop() {
  if (client.available()) {

    BIoTMessage message(client.readString());

    if (message.getEventName() == BIOT_EVENT_UPDATE &&
        message.getDeviceID() == 1 && 
        message.getParamName() == "status" ) { // Checking update event, device id & param name
      
      Serial.println("Update Event => device id : 1, param : status");
      Serial.print(message.getLog());
      
    }


  }

  client.run(server,port,token); //Reconnecting if not connected

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
      client.sendUpdate(1, "status", BIOT_TRUE);
      Serial.println("LED ON");
    }


  }
  else {
    digitalWrite(ledPin, LOW);

    if (currentState == true) {
      currentState = false;
      client.sendUpdate(1, "status", BIOT_FALSE);
     
      Serial.println("LED OFF");
    }
  }

}
```

### Sending update to Server

```cpp
client.sendUpdate(int device_id, String param, String value)
```

### BIoT Message 
It is used to parse the message from the server

##### Creating a message 

```cpp 
BIoTMessage message(client.readString())
```

##### Getting Event Name

```cpp 
message.getEventName() //returns a String
```


##### Getting Device ID 

```cpp
message.getDeviceID() //returns an int
```

##### Getting Parameter Name

```cpp 
message.getParamName() //returns a String
```

##### Getting Parameter Value 

```cpp 
message.getParamValue() //returns a String
```
