#include <Arduino.h>
#include <GPS.h>  // deine eigene Datei vermutlich
#include "GPSManager.h"

void checkForGPSConnection(TinyGPSPlus& gps) {
  ::checkForGPSConnection(gps); // deine bestehende Implementierung
}
