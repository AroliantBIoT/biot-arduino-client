#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

int led1=2;
int led2=4;
int led3=5;
void setup() {
  Serial.begin(9600);
   client.begin(ip, mac);

    Serial.println("connecting...");

    client.connect(server, port, token);

    Serial.println("connected");
    
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
}


void loop() {

   if (client.connected()){

  digitalWrite(led1, HIGH);  
    client.sendUpdate(1, "led1", "true");
  Serial.println("led1 on");
  delay(2000);                    
  digitalWrite(led1, LOW); 
    client.sendUpdate(1, "led1", "false");
  Serial.println("led1 off");
  delay(2000); 
  
  digitalWrite(led2, HIGH);  
    client.sendUpdate(2, "led2", "true");
  Serial.println("led2 on");
  delay(2000);               
  digitalWrite(led2, LOW);
    client.sendUpdate(2, "led2", "false");
  Serial.println("led2 off");  
  delay(2000); 
  
  digitalWrite(led3, HIGH);  
    client.sendUpdate(3, "led3", "true");
  Serial.println("led3 on");
  delay(2000);                    
  digitalWrite(led3, LOW); 
    client.sendUpdate(3, "led3", "false");
  Serial.println("led3 off");
  delay(2000);    

  
                       
}
client.run(server,port,token);
}
