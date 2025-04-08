#ifndef CONFIG_HPP
#define CONFIG_HPP

/* ***************************************************************************
  Global Configuration
*************************************************************************** */

#include "SECRET.hpp"

// #define USE_WIFI
#ifdef USE_WIFI
// #define USE_NTP
// #define USE_OTA
// #define USE_MQTT
#ifdef USE_MQTT
// #define USE_FIREBASE
#endif
#endif

#define USE_SCREEN
#ifdef USE_SCREEN
#define SCREEN_SSD1306
#define USE_BOT_FACE
#endif

#define HEARTBEAT_DELAY 60 * 1000
// Program
#define IOT_VERSION 1.0
#define COPY_LINE1 "    \xA9 2025 by"
#define COPY_LINE2 "** St. Fardoux **"
// WiFi
#define PORTAL_NAME "I.o.T."
// Network Time Protocol
#define NTP_SERVER_EU "europe.pool.ntp.org"
#define NTP_REFRESH 3 * 60 * 60 // 3 hours
#define NTP_SYNC_TIMEOUT 60

#endif