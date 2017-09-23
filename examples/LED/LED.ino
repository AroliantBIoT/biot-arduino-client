#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int led=3;

void setup() {
  Serial.begin(9600);
   client.begin(ip, mac);

    Serial.println("connecting...");

    if (client.connect(server, port, token)) {

    Serial.println("connected");
    }
  
  pinMode(led, OUTPUT);
 
}


void loop() {

   if (client.available()) {
      String message = client.readString();
  }
  
  digitalWrite(led, HIGH);  
    client.sendUpdate(1, "status", "true");
  Serial.println("led on");
  delay(2000);                    
  digitalWrite(led1, LOW); 
    client.sendUpdate(, "status", "false");
  Serial.println("led off");
  delay(2000); 
  
  
  
                       
}
