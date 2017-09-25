#include <DHT.h>
#include <BIoTEthernetClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;

#define DHTPIN 9    
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE); 

int chk;
float hum; 
float temp;
String tempe;
String humi;
void setup()
{
Serial.begin(9600);
client.begin(ip, mac);
Serial.println("connecting...");
client.connect(server, port, token);
Serial.println("connected");
dht.begin();

}

void loop()
{
  if (client.connected()) {
    hum = dht.readHumidity();
    temp= dht.readTemperature();
}
       
Serial.print("Humidity: ");
Serial.print(hum);
Serial.print(" %, Temp: ");
Serial.print(temp);
Serial.println(" Celsius");

humi = String(float(hum));
client.sendUpdate(1,"humidity",humi);
tempe = String(float(temp));
client.sendUpdate(1,"temperature", tempe);
delay(2000);
        
client.run(server,port,token);
}

   