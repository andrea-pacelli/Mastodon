//////////////////////////////////////////////////////////////////
//
// Send toot to Mastodon
// AP2023.
//
//////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <Mastodon.h>
#include <SPI.h>
#include <WiFiNINA.h>

#include "arduino_secrets.h"

WiFiSSLClient client;
const char *hostname = SECRET_HOSTNAME;
const char *ssid = SECRET_SSID;
const char *pass = SECRET_PASS;

Mastodon masto;
const char *server = SECRET_SERVER;
const char *token = SECRET_TOKEN;

void setup(void) {
  Serial.begin(9600);
  while (!Serial)
    yield();
  Serial.print("Connecting to SSID ");
  Serial.println(ssid);

  int status = WiFi.begin(ssid, pass);
  if (status != WL_CONNECTED) {
    Serial.println("Failed to connect");
    while (true)
      ;
  }
  else
    Serial.println("Connected");
}

void loop(void) {
  const char *status = "Test Toot";
 
  masto.begin(server, token, &client);
  Serial.println("Sending toot");
  int returnCode = masto.toot(status);
  Serial.print("Return code: ");
  Serial.println(returnCode);
  while (true)
    ;
}

