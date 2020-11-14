/* 

  Name: Raghu Vamsi Veerapaneni
  Roll No: 1701EE35
  Topic: DHT11 sensor module analysis week_3

  In here we compare real values with the values printed by DHT11 sensor module on serial monitor

*/

#include "dht.h"
#define dht_out_pin A0                        // Analog Pin sensor
 
dht DHT;                                      //object DHT of class dht
 
void setup(){                                 //setup code begins
 
  Serial.begin(9600);                         //Baud rate
  delay(500);                                 //Delay
  Serial.println("DHT11 Humidity & temperature Sensor\n\n");
  delay(1000);                                //Delay
 
}
 
void loop(){                                  //loop code begins
 
    DHT.read11(dht_out_pin);                  //DHT11 uses read11
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(6000);                              //delay 6sec
 
}
