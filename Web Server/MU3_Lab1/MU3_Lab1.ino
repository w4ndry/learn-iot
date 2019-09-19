#include <WiFi.h>
const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect(true);
  connectToHotSpot();
}
void connectToHotSpot() {
  WiFi.begin( SSID, PASSWORD );
  Serial.print("Trying to establish connection to WiFi Router");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected! IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" dan Mac Address: ");
  Serial.print(WiFi.macAddress());
  Serial.println();
  Serial.println(WiFi.localIP());
}
void loop() {
// nothing here
}
