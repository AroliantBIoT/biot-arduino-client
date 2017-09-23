#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <BIoTEthernetClient.h>
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 100, 177 };

byte server[] =  { 192, 168 , 100 , 10 };
int port = 5001 ;
String token = "12345";

BIoTEthernetClient client;



Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


void displaySensorDetails(void)
{
  sensor_t sensor;
  bmp.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" hPa");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" hPa");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" hPa");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}


void setup(void) 
{
  Serial.begin(9600);
   client.begin(ip, mac);

    Serial.println("connecting...");

    if (client.connect(server, port, token)) {

    Serial.println("connected");
    }
  Serial.println("Pressure Sensor Test"); Serial.println("");
   client.sendUpdate(1, "status", "tested");
 
  if(!bmp.begin())
  {
    
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  
  displaySensorDetails();
}


void loop(void) 
{
 if (client.available()) {
      String message = client.readString();
  }
  
  sensors_event_t event;
  bmp.getEvent(&event);
 
 
  if (event.pressure)
  {
   
    Serial.print("Pressure:    ");
    Serial.print(event.pressure);
    Serial.println(" hPa");
    
   
    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    
    float seaLevelPressure = SENSORS_PRESSURE_SEALEVELHPA;
    Serial.print("Altitude:    "); 
    Serial.print(bmp.pressureToAltitude(seaLevelPressure,
                                        event.pressure)); 
    Serial.println(" m");
    Serial.println("");
     client.sendUpdate(1, "status", "true");
  }
  else
  {
    Serial.println("Sensor error");
     client.sendUpdate(1, "status", "false");
  }
  delay(3000);
}
