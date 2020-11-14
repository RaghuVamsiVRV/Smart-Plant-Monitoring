
#define BLYNK_PRINT Serial


#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <DHT.h>


char auth[] = "kNO9oNe05JkV1V8Yy55rDk**inJK-MJQK";

char ssid[] = "POCO";
char pass[] = "12345678";


#include <SoftwareSerial.h>
SoftwareSerial EspSerial(2, 3); // RX, TX

// Your ESP8266 baud rate:
#define ESP8266_BAUD 115200

ESP8266 wifi(&EspSerial);

#define DHTPIN A0          


#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;


const int HMoisture = 250;                    //When sensor is dipped in water         
const int LMoisture = 650; 
int OMoisture;

void sendSensor()
{
  int m = analogRead(A1);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  OMoisture = map(m, LMoisture, HMoisture, 0, 100);
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
  Blynk.virtualWrite(V4, OMoisture);


  if(OMoisture > 90)
  {
    Blynk.notify("Soil is wet, Flooded!!");
  }
  else if(OMoisture < 20)
  {
    Blynk.notify("Soil is dry, Need to water");
  }
  else
  {
    Blynk.notify("Normal");
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);


  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
