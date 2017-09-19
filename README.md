# BIoT-Arduino-Client
Download the BIoTClient library and include in the project.
```cpp
#include <BIoTClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTClient client;

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

  // Button Press

  //client.sendUpdate(1,"status","true");

}
```
