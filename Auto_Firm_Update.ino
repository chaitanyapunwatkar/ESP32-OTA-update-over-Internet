#include <ESP32httpUpdate.h>
#include "Arduino.h"
#include <WiFi.h>
#include <HTTPClient.h>

String version = "1.0.0.3";
String CHIPID = "E04894B5AA8C";
void doUpdate();
void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin("geomitra-incub", "incub123#");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println(".");
    delay(150);
  }

  Serial.print("Wifi IP:");
  Serial.println(WiFi.localIP());

  // Setup LED GPIO
  pinMode(2, OUTPUT);
  Serial.println(version);
}

int updateCheckTimer = 0;
void loop()
{
  // Lets blink
  digitalWrite(2, 1);
  delay(100);
  digitalWrite(2, 0);
  delay(100);

  updateCheckTimer++;
  if (updateCheckTimer > 30)
  {
    updateCheckTimer = 0;
    check();
  }
}

void check() {
  HTTPClient http;
  String serverName = "http://theweightmeasure.000webhostapp.com/check.txt";
  http.begin(serverName);

  // Send HTTP GET request
  int httpResponseCode = http.GET();
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload);
    http.end();
    if (payload == "1") {
      Serial.println("Updating Firmware");
      post();
      doUpdate();
      
    }
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }


}
void post() {
  HTTPClient http;
  String serverName = "http://theweightmeasure.000webhostapp.com/value.php";
  http.begin(serverName);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String httpRequestData = "Text1=1000";
  int httpResponseCode = http.POST(httpRequestData);
  Serial.println("Posted check: 100");
  http.end();
}
void doUpdate()
{
  String url = "http://theweightmeasure.000webhostapp.com/firm.bin";
  //url += "&s=" + CHIPID;
  //url += "&v=" + version;

  t_httpUpdate_return ret = ESPhttpUpdate.update(url);
  switch (ret)
  {
    case HTTP_UPDATE_FAILED:
      Serial.println("Update failed!");
      break;
    case HTTP_UPDATE_NO_UPDATES:
      Serial.println("No new update available");
      break;
    // We can't see this, because of reset chip after update OK
    case HTTP_UPDATE_OK:
      Serial.println("Update OK");
      break;

    default:
      break;
  }
}
