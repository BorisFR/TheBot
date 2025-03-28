#ifndef THE_NTP_HPP
#define THE_NTP_HPP

#include "../../../src/CONFIG.hpp"
#include "WiFi.h"
#include <WiFiUdp.h>
#include <ezTime.h>

class TheNTP
{
public:
    TheNTP();
    void setup();
    void loop();
    String currentDateTime(String format);

private:
    WiFiUDP ntpUDP;
    Timezone timeZone;
    bool ntpOk;
};

#endif