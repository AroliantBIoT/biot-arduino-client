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

      if ( message.getParamValue() == BIOT_TRUE ) {
        Serial.println("Turning ON LED");
        digitalWrite(led, HIGH);
      } else {
        Serial.println("Turning OFF LED");
        digitalWrite(led, LOW);
      }
    }


  }

  client.run(server,port,token); //Reconnecting if not connected

}