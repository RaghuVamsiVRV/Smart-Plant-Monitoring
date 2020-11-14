/* 
  Name: Raghu Vamsi Veerapaneni
  Roll No: 1701EE35
  Topic: Soil Moisture Analysis Week_2

  In here we declare constant values like: HMoisture, MMoisture, LMoisture
  Output i.e., Real time moisture: OutMoisture (Variable), OMoisture(in %)

  OutMoisture > HMoisture - No need to water a plant, Soil is wet
  OutMoisture > LMoisture - Need to water a plant, Soil is dry
*/


const int HMoisture = 250;          //When sensor is dipped in water         
const int LMoisture = 600;          //When sensor is present in air

int OutMoisture = 300;              //Initialising with MMoisture
int OMoisture = 50;                 

void setup() {                      // put your setup code here, to run once
  Serial.begin(9600);               //baud rate is 9600
}

void loop() {                       // put your main code here, to run repeatedly:
  OutMoisture = analogRead(A0);     // Analog Output at A0
  Serial.print("Moisture present in soil: ");
  Serial.print(OutMoisture);    
  OMoisture = map(OutMoisture, LMoisture, HMoisture, 0, 100);
  if(OMoisture >= 100)
  {
    Serial.println("- (100%)");
    Serial.println("Soil is wet, Flooded (Critical)");
  }
  else if(OMoisture <= 0)
  {
    Serial.println("- (0%)");
    Serial.println("Soil is dry, Need to water a plant! (Critical)");
  }
  else
  {
    Serial.print("- (");
    Serial.print(OMoisture);
    Serial.println("%)");
    if(OutMoisture>=560)
    {
      Serial.println("Soil is dry, Need to water a plant! (Critical)");
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
      Serial.println("Soil is wet, Flooded (Critical)");
    }
    else
    {
      Serial.println("Normal");
    }
  }
  delay(6000);
}
