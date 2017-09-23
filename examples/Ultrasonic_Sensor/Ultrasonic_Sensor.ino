#include <BIoTEthernetClient.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };
byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
void setup() {
  Serial.begin(9600);
  client.begin(ip, mac);

  Serial.println("connecting...");

  client.connect(server, port, token);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delay(1000);
  digitalWrite(trigPin, LOW);

  //duration = pulseIn(echoPin, HIGH);
  duration = 0;

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm ");

  if(client.connected()){
    Serial.println("Client is connected");
    client.sendUpdate(1, "status", "true");
  }else{
    Serial.println("Client not connected");
    client.connect(server, port, token);
  }
  
}
