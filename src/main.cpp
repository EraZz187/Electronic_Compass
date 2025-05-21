#include <Arduino.h>
#include "WiFiManager.h"
#include "OTAHandler.h"
#include "mDNSHandler.h"
#include "GPSManager.h"
#include <TinyGPSPlus.h>
#include "WebServerHandler.h"

// Zugangsdaten und Netzwerkkonfiguration
const char *ap_ssid = "Locatinator";
const char *ap_password = "12345678";
const char *sta_ssid = "TurkishAirlines_";
const char *sta_password = "123Polizei";
const char *sta_hostname = "locatinator";

IPAddress local_IP(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

WiFiServer server(80);
TinyGPSPlus gps;

void setup()
{
  Serial.begin(115200);
  Serial.println("Booting");

  connectToWiFi(sta_ssid, sta_password, 10);                         // Verbindet sich mit dem WLAN (Station-Modus)
  startAccessPoint(ap_ssid, ap_password, local_IP, gateway, subnet); // Startet eigenen Access Point (AP-Modus)
  setupOTA(sta_hostname);                                            // Initialisiert OTA (Over-the-Air) Updates
  setupMDNS(sta_hostname);                                           // Startet mDNS-Dienst (z. B. locatinator.local erreichbar)
  server.begin();
}

void loop()
{
  handleOTA();                                                       // Handhabt eingehende OTA-Anfragen
  checkForGPSConnection(gps);                                        // Überprüft GPS-Datenverbindung
  handleClient(server);
}
