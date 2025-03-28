#include "CONFIG.hpp"
#include <Arduino.h>

bool dataChanged = false;
unsigned long memoSendsLastTime;
String uid = "";

/* ***************************************************************************
  Json
*************************************************************************** */
#include <ArduinoJson.h>
JsonDocument jsonData;

/* ***************************************************************************
  Settings
*************************************************************************** */
#include "TheSettings.hpp"
TheSettings theSettings;

#ifdef USE_WIFI
/* ***************************************************************************
  WiFi
*************************************************************************** */
#include "TheWifi.hpp"
TheWifi theWifi;
void theWifiChangeIP(String value)
{
#ifdef USE_SCREEN
  theScreen.changeValue(3, value);
#endif
  jsonData["ip"] = value;
}
#endif

#ifdef USE_OTA
/* ***************************************************************************
  OTA
*************************************************************************** */
#include "TheOTA.hpp"
TheOTA theOTA;
#endif

#ifdef USE_NTP
/* ***************************************************************************
  NTP
*************************************************************************** */
#include "TheNTP.hpp"
TheNTP theNTP;
#endif

#ifdef USE_MQTT
/* ***************************************************************************
  MQTT
*************************************************************************** */
#pragma region
#include "TheMQTT.hpp"
TheMQTT theMQTT;

void receivedData(char *topic, byte *payload, unsigned int length)
{
  JsonDocument document;
  deserializeJson(document, payload, length);
  String jsonString;
  serializeJson(document, jsonString);
  Serial.println("Received JSON: " + jsonString);
#ifdef USE_SENSOR
  unsigned long temp = document["sensor_delay"];
  if (temp != sensorsDelay)
  {
    Serial.println("Change sensor delay from " + String(sensorsDelay) + " to " + String(temp));
    sensorsDelay = temp;
    theSettings.settingsSaveOneUL(SETTINGS_SENSOR_DELAY, sensorsDelay);
  }
#endif
}

void publishData(String topic, JsonDocument data)
{
  data["timestamp"] = dateTime("YmdHis");
  data["rssi"] = -WiFi.RSSI();
  String message;
  serializeJson(data, message);
  theMQTT.publish(topic, message);
}

void mqttConnected()
{
  jsonData["version"] = IOT_VERSION;
  jsonData["platform"] = IOT_PLATFORM;
  // jsonData["ota_user"] = OTA_USER;
  jsonData["ota_password"] = OTA_PASSWORD;
#ifdef USE_SENSOR
  jsonData["sensor_delay"] = sensorsDelay;
#endif
  publishData("device", jsonData);
  // jsonData.remove("ota_user");
  jsonData.remove("ota_password");
  jsonData.remove("sensor_delay");
  jsonData.remove("version");
  jsonData.remove("platform");
  jsonData.remove("attach");
}
#pragma endregion
#endif

#ifdef USE_SCREEN
/* ***************************************************************************
  Screen
*************************************************************************** */
#pragma region
#include "TheScreen.hpp"
TheScreen theScreen;
#pragma endregion
#endif

#ifdef USE_BOT_FACE
/* ***************************************************************************
  BOT FACE
*************************************************************************** */
#pragma region
#include "TheBotFace.hpp"
TheBotFace theBotFace;
// TheBotFace theBotFace(SCREEN_WIDTH, SCREEN_HEIGHT, 40);
#pragma endregion
#endif

void setup()
{
  Serial.begin(115200);
  delay(1500);
  Serial.println("** I.o.T.");
  Serial.println("Version: " + String(IOT_VERSION));
  Serial.println("Platform: " + String(IOT_PLATFORM));
  theSettings.setup();
#ifdef USE_WIFI
  theWifi.eventChangeIP(theWifiChangeIP);
  uid = "ESP32-" + theWifi.getMacAddress();
  Serial.println("UID: " + uid);
  jsonData["id"] = uid;
  delay(500);
#endif
#ifdef USE_WIFI
  theWifi.setup();
#endif
#ifdef USE_OTA
  theOTA.setup();
#endif
  delay(500);
#ifdef USE_NTP
  theNTP.setup();
#endif
#ifdef USE_MQTT
  theMQTT.eventConnected(mqttConnected);
  theMQTT.eventReceive(receivedData);
  theMQTT.setup();
#endif
#ifdef USE_SCREEN
  theScreen.setup();
#endif
#ifdef USE_BOT_FACE
  theBotFace.setup();
  theBotFace.setScreenDimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
  theBotFace.setEyeSize(40);
  theBotFace.Expression.GoTo_Normal();
  // Assign a weight to each emotion
  // theBotFace.Behavior.SetEmotion(eEmotions::Normal, 1.0);
  // theBotFace.Behavior.SetEmotion(eEmotions::Angry, 1.0);
  // theBotFace.Behavior.SetEmotion(eEmotions::Sad, 1.0);
  // Automatically switch between behaviours (selecting new behaviour randomly based on the weight assigned to each emotion)
  theBotFace.RandomBehavior = true;
  theBotFace.Behavior.Timer.SetIntervalMillis(2500);

  // Automatically blink
  theBotFace.RandomBlink = true;
  // Set blink rate
  theBotFace.Blink.Timer.SetIntervalMillis(4373);

  // Automatically choose a new random direction to look
  theBotFace.RandomLook = true;
#endif
}

void loop()
{
#ifdef USE_WIFI
  theWifi.loop();
#endif
#ifdef USE_OTA
  theOTA.loop();
#endif
#ifdef USE_NTP
  theNTP.loop();
#endif
#ifdef USE_MQTT
  theMQTT.loop();
#endif
#ifdef USE_MQTT
  if (millis() - memoSendsLastTime >= HEARTBEAT_DELAY)
    dataChanged = true;
  if (dataChanged)
  {
    publishData("sensors", jsonData);
    memoSendsLastTime = millis();
  }
  dataChanged = false;
#endif
#ifdef USE_BOT_FACE
  theBotFace.loop();
#endif
#ifdef USE_SCREEN
  theScreen.loop();
#endif
}
