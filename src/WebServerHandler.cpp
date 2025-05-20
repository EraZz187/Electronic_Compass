#include "WebServerHandler.h"

void handleClient(WiFiServer &server) {
  WiFiClient client = server.available();
  if (!client) return;

  Serial.print("\n🔗 Client verbunden");

  String request = "";
  while (client.connected()) {
    if (client.available()) {
      char c = client.read();
      request += c;
      if (request.endsWith("\r\n\r\n")) {
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println("Connection: close");
        client.println();
        client.println("<!DOCTYPE html><html><body>");
        client.println("<h1>ESP32 Dual Mode</h1>");
        client.println("<h1>Hoi Dario</h1>");
        client.print("<p>STA-IP: ");
        client.print(WiFi.localIP());
        client.println("</p>");
        client.print("<p>AP-IP: ");
        client.print(WiFi.softAPIP());
        client.println("</p>");
        client.println("</body></html>");
        break;
      }
    }
  }

  client.stop();
  Serial.println("❎ Client getrennt");
}
