
#include <DHT.h>
#include <BIoTEthernetClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;


#define DHTPIN 5    
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE); 



int chk;
float hum; 
float temp;

void setup()
{
  Serial.begin(9600);
    client.begin(ip, mac);

  Serial.println("connecting...");

  if (client.connect(server, port, token)) {

    Serial.println("connected");
  dht.begin();
}
}

void loop()
{
   if (client.available()) {
    String message = client.readString();
  }

    delay(1000);
    
    hum = dht.readHumidity();
    temp= dht.readTemperature();
        client.sendUpdate(1, "status", "true");
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    delay(2000);
}

   
