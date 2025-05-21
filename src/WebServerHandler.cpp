#include "WebServerHandler.h"
#include <WiFi.h>
#include "WiFiManager.h"
#include "SPIFFS.h"

void handleClient(WiFiServer &server) {
  WiFiClient client = server.available();
  if (!client) return;

  String request = "";
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;
      if (request.endsWith("\r\n\r\n")) {
        routeRequest(request, client);  // Dynamischer Router
        break;
      }
    }
  }

  client.stop();
  Serial.println("❎ Client getrennt");
}

void routeRequest(const String &request, WiFiClient &client) {
  String path = "/index.html";  // Default

  // Erste Zeile aus Request extrahieren (bis \r\n)
  int firstLineEnd = request.indexOf("\r\n");
  String firstLine = request.substring(0, firstLineEnd);

  // Pfad aus erster Zeile parsen: z.B. "GET /sensor HTTP/1.1"
  int firstSpace = firstLine.indexOf(' ');
  int secondSpace = firstLine.indexOf(' ', firstSpace + 1);
  if (firstSpace >= 0 && secondSpace > firstSpace) {
    path = firstLine.substring(firstSpace + 1, secondSpace);
    if (path == "/") path = "/index.html";  // Root auf Index umleiten
  }

  // Spezielle API-Route abfangen
  if (path == "/sensor") {
    int wert = 112358;
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: application/json");
    client.println("Connection: close");
    client.println();
    client.printf("{\"wert\": %d}", wert);
    return;
  }

  // Sonst statische Datei laden
  String html = loadHtmlFile(path.c_str());
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println("Connection: close");
  client.println();
  client.println(html);
}


String loadHtmlFile(const char* path) {
  File file = SPIFFS.open(path);
  if (!file || file.isDirectory()) return "<h1>Datei nicht gefunden</h1>";
  String content = file.readString();
  file.close();
  content.replace("{{STA_IP}}", WiFi.localIP().toString());
  content.replace("{{AP_IP}}", WiFi.softAPIP().toString());
  return content;
}
