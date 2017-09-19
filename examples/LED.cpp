/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 19 Sep 2017 
 by Arjun Durai
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <BIoTEthernetClient.h>
#include <Servo.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;
Servo myservo;
int pos = 0;
int val;
String value;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  client.begin(ip, mac);

  Serial.println("connecting...");

  if (client.connect(server, port, token)) {

    Serial.println("connected");
   myservo.attach(9);
  }

}


void loop() {

  if(client.available()){

    String message = client.readString();

    if(client.getEventName(message) == client.EVENT_UPDATE){
      Serial.println("Update Event Received");

     if(client.getDeviceID(message) == 2){

     	value = client.getParamValue(message);
     	val = analogRead(value.toInt())
     } 
    }
  }
}