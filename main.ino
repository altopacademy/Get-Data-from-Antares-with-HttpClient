#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to WiFi");
  WiFi.begin("Wokwi-GUEST", "", 6);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(" Connected!");
  
}

void loop() {
    if(WiFi.status()== WL_CONNECTED){   //Check WiFi connection status
  
   HTTPClient http;   
  
   http.begin("https://platform.antares.id:8443/~/antares-cse/antares-id/SmartHome101/Temperature/la");  //Specify destination for HTTP request
   http.addHeader("X-M2M-Origin", "*************************");
   http.addHeader("Content-Type", "application/json");            //Specify content-type header
   String body = "{\"temperature\":\"" + String(random(50)) + "\",\"humidity\":\"" + String(random(50)) + "\"}";
   int httpResponseCode = http.GET();   //Send the actual POST request
  
   if(httpResponseCode>0){
  
    String response = http.getString();                       //Get the response to the request
  
    Serial.println(httpResponseCode);   //Print return code
    Serial.println(response);           //Print request answer
  
   }else{
  
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  
   }
  
   http.end();  //Free resources
  
 }else{
  
    Serial.println("Error in WiFi connection");   
  
 }
  
  delay(10000);  //Send a request every 10 seconds
 
}
