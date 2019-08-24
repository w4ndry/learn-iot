#include <DHTesp.h>

DHTesp dht;

#define PIN_DHT 15

void setup() {
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Serial.print("Status\tHumidity(%) ");
  Serial.println("\tTemperatur (Celcius)");

}

void loop() {
  delay(dht.getMinimumSamplingPeriod());

  Serial.print(dht.getStatusString());
  Serial.print("\t");

  Serial.print(dht.getHumidity());
  Serial.print("\t");

  Serial.print(dht.getTemperature());
  Serial.println();
}
