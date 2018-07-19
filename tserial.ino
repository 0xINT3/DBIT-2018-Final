#include <ESP8266WiFi.h>
#include <Wire.h> 
 ;
// replace with your channel's thingspeak API key, 
int WET = 16; // Wet Indicator at Digital PIN D0
int DRY = 2; // Dry Indicator at Digital PIN D4

int sense_Pin = 0; // Soil Sensor input at Analog PIN A0
int value = 0;

String apiKey = "*********";       #enter your thingspeak API
const char* ssid = "******";
const char* password = "******";
 
String host = "maker.ifttt.com/trigger/";
String url = "HydroSMS/with/key/***********";


const char* server = "api.thingspeak.com";
 
WiFiClient client;
void setup()

{     
  Serial.begin(115200);
  pinMode(A0,INPUT);
  delay(10);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   Serial.begin(9600);
  pinMode(WET, OUTPUT);
  pinMode(DRY, OUTPUT);
  delay(2000);
  
}
 
 
void loop() {
  int temp = analogRead(A0);
 
  if (client.connect(server,80)) {  //   "184.106.153.149" or api.thingspeak.com
    String postStr = apiKey;
           postStr +="&field1=";
           postStr += String(temp);
           postStr += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n"); 
     client.print("Host: api.thingspeak.com\n"); 
     client.print("Connection: close\n"); 
     client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n"); 
     client.print("Content-Type: application/x-www-form-urlencoded\n"); 
     client.print("Content-Length: "); 
     client.print(postStr.length()); 
     client.print("\n\n"); 
     client.print(postStr);

     if(temp>700)
     {
        Serial.print("TDS High! Water not safe for drinking.\n\n");
        Serial.print("Value; \n");
        Serial.print(temp);
     }

     else if(temp<700)
     {
      Serial.print("TDS Low! Water is safe for drinking. \n\n");
      Serial.print("Value: \n");
      Serial.print(temp);
     }
    
    
  }
  /*
  if(millis() > 10000){
        client.print(String("GET "+url+"HTTP/1.1\r\n")+"Host: "+host+"\r\n"+"Connection: close\r\n\r\n");
        Serial.println("Check for SMS");  
  }
  */
  
  client.stop();

   Serial.println("\nWaiting...");    
          
}
