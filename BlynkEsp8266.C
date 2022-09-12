#define BLYNK_PRINT Serial    
#include <SPI.h>
#include <ESP8266WiFi.h>

#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "Key in Blynk";    
char ssid[] = "SSD";                           
char pass[] = "PASSWORD";

#define DHTPIN 2 
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void setup()
{
  
  Blynk.begin(auth, ssid, pass);

  dht.begin();
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, ReceberDados);
  Serial.begin(9600);
}

void sendSensor()
{
   float h = dht.readHumidity();
   float t = dht.readTemperature();  
   Blynk.virtualWrite(V5, h);  
   Blynk.virtualWrite(V6, t);  

 }

 //void ReceberDados(){
 //if(Serial.available())
 //{
   //int umidade = Serial.parseInt();
   //Serial.println(umidade);
   //Blynk.virtualWrite(V7, umidade); 
 //}}

void loop()
{
  //ReceberDados();
  Blynk.run();
  timer.run(); 
}