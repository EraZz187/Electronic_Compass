#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <OverTheAir.h>
#include <TinyGPSPlus.h>
#include <GPS.h>

//Wifi Connection
const char* ssid = "TurkishAirlines_";
const char* password = "123Polizei";
const char* hostname = "eCompass";

// The TinyGPSPlus object
TinyGPSPlus gps;

void setup(void) {
  Serial.begin(115200); 
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  OverTheAirSetup(hostname);
  
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(hostname)) // electronicCompass.local
  {
    Serial.println("Error setting up mDNS.");
  }
  MDNS.addService("http", "tcp", 80);
}

void loop(void) {
  OverTheAirHandle();
  checkForGPSConnection(gps);
}