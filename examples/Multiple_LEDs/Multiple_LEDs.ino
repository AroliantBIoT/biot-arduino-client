#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int led1=3;
int led2=4;
int led3=5;
void setup() {
  Serial.begin(9600);
   client.begin(ip, mac);

    Serial.println("connecting...");

    if (client.connect(server, port, token)) {

    Serial.println("connected");
    }
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}


void loop() {

   if (client.available()) {
      String message = client.readString();
  }
  
  digitalWrite(led1, HIGH);  
    client.sendUpdate(1, "status", "true");
  Serial.println("led1 on");
  delay(2000);                    
  digitalWrite(led1, LOW); 
    client.sendUpdate(1, "status", "false");
  Serial.println("led1 off");
  delay(2000); 
  
  digitalWrite(led2, HIGH);  
    client.sendUpdate(2, "status", "true");
  Serial.println("led2 on");
  delay(2000);               
  digitalWrite(led2, LOW);
    client.sendUpdate(2, "status", "false");
  Serial.println("led2 off");  
  delay(2000); 
  
  digitalWrite(led3, HIGH);  
    client.sendUpdate(3, "status", "true");
  Serial.println("led3 on");
  delay(2000);                    
  digitalWrite(led3, LOW); 
    client.sendUpdate(3, "status", "false");
  Serial.println("led3 off");
  delay(2000);    

  
                       
}
