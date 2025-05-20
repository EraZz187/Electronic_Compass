#include <OverTheAir.h>
#include "OTAHandler.h"

void setupOTA(const char* hostname) {
  OverTheAirSetup(hostname);
}

void handleOTA() {
  OverTheAirHandle();
}
