#include <Arduino.h>
#include "WiFiManager.h"
#include "WebServerHandler.h"

const char *ap_ssid = "Locatinator";
const char *ap_password = "12345678";
const char *sta_ssid = "TurkishAirlines_";
const char *sta_password = "123Polizei";

IPAddress local_IP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);

  connectToWiFi(sta_ssid, sta_password, 10);
  startAccessPoint(ap_ssid, ap_password, local_IP, gateway, subnet);

  server.begin();
}

void loop() {
  handleClient(server); // ausgelagert
}
