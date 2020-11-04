#include "cred.h"

MDNSResponder mdns;
ESP8266WebServer server(80);

#include "handleRoot.h"
#include "handleRaw.h"
#include "clearEEPROM.h"

void WiFiAP() {
  Serial.print("Setting soft-AP ... ");
  int channel = 1,  ssid_hidden = 0;
  boolean result = WiFi.softAP(ssid, password, channel, ssid_hidden);
  if(result == true)
  {
    Serial.println("Ready");
  }
  else
  {
    Serial.println("Failed!");
  }
  
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.on("/", handleRoot );
  server.on("/raw", handleRaw);
  server.on("/eeprom", clearEEPROM);


//  server.onNotFound(setByURL);

  server.begin();
}

void WiFiCl() {
 WiFi.begin(ssid, password);
  Serial.println("");
  delay(100);
  Serial.print("Connecting .");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot );
  server.on("/raw", handleRaw);
  server.on("/eeprom", clearEEPROM);


//  server.onNotFound(setByURL);

  server.begin();
}
