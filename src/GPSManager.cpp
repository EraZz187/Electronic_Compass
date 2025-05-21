#include "GPSManager.h"
#include <TinyGPSPlus.h>

uint32_t checkForGPSConnection(TinyGPSPlus &gps)
{
  return gps.satellites.value() > 0;
};