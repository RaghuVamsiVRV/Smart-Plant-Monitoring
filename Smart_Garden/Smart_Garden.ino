/* 

  Name: Raghu Vamsi Veerapaneni
  Roll No: 1701EE35
  Topic: Smart Garden project with help of Capacitive soil moisture sensor and DHT11 sensor module week_4

  In here we implement a complete hardware side of smart garden project. 
  We will address border conditions arised in Capacitive soil moisture sensor by involving DHT11 sensor module

  Below pseudocode varies according to location and type of plant

  if soil_moisture is high
    if temperature > 40 and relative humidity < 70  (soil might turn dry soon)
    if temperature > 40 and relative humidity > 90  (normal)

    if temperature < 25 and relative humidity < 70  (normal)
    if temperature < 25 and relative humidity > 90  (Flooded, enough water)

  if soil_moisture is low
    if temperature > 40 and relative humidity < 70  (DRY, Alert! Need Water)
    if temperature > 40 and relative humidity > 90  (Need Water)

    if temperature < 25 and relative humidity < 70  (DRY, Need Water)
    if temperature < 25 and relative humidity > 90  (Need Water)

*/

#include "dht.h"
#define dht_out_pin A1                        // Analog Pin sensor

dht DHT;                                      //object DHT of class dht

const int HMoisture = 250;                    //When sensor is dipped in water         
const int LMoisture = 600;                    //When sensor is present in air
int OutMoisture;
int OMoisture;
float temperature;
float humidity;
            

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);                         //Baud rate
  delay(500);                                 //Delay
  Serial.println("Smart Garden\n\n");
  delay(1000); 
}

void loop() {
  // put your main code here, to run repeatedly:
  DHT.read11(dht_out_pin);                    //DHT11 uses read11

  OutMoisture = analogRead(A0);               // Analog Output at A0
 
  OMoisture = map(OutMoisture, LMoisture, HMoisture, 0, 100);

  temperature = DHT.temperature;
  humidity = DHT.humidity;
  
  Serial.print("Current humidity = ");
  Serial.print(humidity);
  Serial.print("%  ");
  Serial.print("Temperature = ");
  Serial.print(temperature); 
  Serial.println("C  ");
  Serial.print("Soil Moisture = ");

  if(OMoisture >= 100)
  {
    Serial.println("100%  ");
    Serial.println("Soil is wet, Flooded (Critical)");
  }
  else if(OMoisture <= 0)
  {
    Serial.println("0%  ");
    Serial.println("Soil is dry, Need to water a plant! (Critical)");
  }
  else
  {
    Serial.print(OMoisture);
    Serial.println("%  ");
  }
  
  if(OutMoisture>=560)
  {
    if(temperature > 40 and humidity < 70)
    {
      Serial.println("Soil is dry, Need to water a plant! (Critical)");
    }
    else if(temperature < 25 and humidity < 70)
    {
      Serial.println("Soil is dry, Need to water a plant");
    }
    else
    {
      Serial.println("Dry, Need to water a plant");
    }
  }
  else if(OutMoisture>=450)
  {
    Serial.println("Need to water a plant");
  }
  else if(OutMoisture>=300)
  {
    Serial.println("Normal");
  }
  else if(OutMoisture<=260)
  {
    if(temperature > 40 and humidity < 70)
    {
      Serial.println("Soil is wet, Stop watering");
    }
    else if(temperature < 25 and humidity > 90)
    {
      Serial.println("Flooded, enough watering the plant");
    }
    else
    {
      Serial.println("Wet, Stop watering");
    }
  }
  else
  {
    Serial.println("Normal");
  }
  delay(6000);
  
}
