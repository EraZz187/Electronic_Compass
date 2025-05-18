#include <TinyGPSPlus.h>

bool checkForGPSConnection(TinyGPSPlus &gps)
{
  return gps.satellites.value() > 0;
};