#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int ledPin = 13;
int irPin = 6;
int val = 0;
bool irState = LOW;

void setup() 
{
    Serial.begin(57600);
  
  client.begin(ip, mac);

    Serial.println("connecting...");

    if (client.connect(server, port, token)) {

    Serial.println("connected");

  pinMode (ledPin,OUTPUT);
  pinMode (irPin, INPUT);
}
}
void loop () 
{
  if (client.available()) {
      String message = client.readString();
  }

  val = digitalRead(irPin);
  Serial.println(val);

if (val == HIGH){
  digitalWrite(ledPin,HIGH);

if (pirState == LOW) {
  Serial.println("Motion detected!");
     
    pirState = HIGH;
      client.sendUpdate(1, "status", "true");
     
   }
}
else{
digitalWrite(ledPin,LOW);
if (pirState == HIGH) {
     pirState = LOW;
      client.sendUpdate(1, "status", "false");
     
   
}

}
}

