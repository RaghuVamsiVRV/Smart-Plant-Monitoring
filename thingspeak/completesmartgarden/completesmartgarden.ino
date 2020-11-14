#include <SoftwareSerial.h>

#include "dht.h"
#define RX 2
#define TX 3
String AP = "POCO";       // AP NAME
String PASS = "12345678"; // AP PASSWORD
String API = "IITDK08F8***TF0C4";   // Write API KEY
String HOST = "api.thingspeak.com";
String PORT = "80";
String field = "field1";
int countTrueCommand;
int countTimeCommand; 
boolean found = false; 

SoftwareSerial esp8266(RX,TX); 

const int HMoisture = 250;          //When sensor is dipped in water         
const int LMoisture = 600;          //When sensor is present in air

int OMoisture = 50;
int OutMoisture = 600;

int moSensor = 1;
int teSensor = 1;
int huSensor = 1;

#define dht_out_pin A1
dht DHT;    
  
void setup() {
  Serial.begin(9600);
  esp8266.begin(115200);
  sendCommand("AT",5,"OK");
  sendCommand("AT+CWMODE=1",5,"OK");
  sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK");
}

void loop() {
 DHT.read11(dht_out_pin);    
 moSensor = getMoData();
 teSensor = getTeData();
 huSensor = getHuData();
 String getData = "GET /update?api_key="+ API +"&field1="+String(moSensor)+"&field2="+String(teSensor)+"&field3="+String(huSensor);
sendCommand("AT+CIPMUX=1",5,"OK");
 sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK");
 sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">");
 esp8266.println(getData);delay(1500);countTrueCommand++;
 sendCommand("AT+CIPCLOSE=0",5,"OK");
}

int getMoData(){
  OutMoisture = analogRead(A0);     // Analog Output at A0
  Serial.print("Moisture present in soil: ");
  Serial.print(OutMoisture);    
  OMoisture = map(OutMoisture, LMoisture, HMoisture, 0, 100);
  return OMoisture; // Replace with your own sensor code
}

int getTeData(){
  return DHT.temperature;
}

int getHuData(){
  return DHT.humidity;
}

void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");
  while(countTimeCommand < (maxTime*1))
  {
    esp8266.println(command);//at+cipsend
    if(esp8266.find(readReplay))//ok
    {
      found = true;
      break;
    }
  
    countTimeCommand++;
  }
  
  if(found == true)
  {
    Serial.println("OYI");
    countTrueCommand++;
    countTimeCommand = 0;
  }
  
  if(found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }
  
  found = false;
 }
