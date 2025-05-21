#pragma once
#include <WiFi.h>

void handleClient(WiFiServer &server);
void routeRequest(const String &request, WiFiClient &client);
String loadHtmlFile(const char* path);