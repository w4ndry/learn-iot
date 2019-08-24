#include <DHT.h>

#define PIN_DHT 15
#define DHT_TYPE DHT11

DHT dth (PIN_DHT, DHT_TYPE);

float humidity;
float temperature;

void setup() {
  dht.begin();
}

void loop() {
  humidity = dht.getHumidity();
  temperature = dht.getTemperature();

  if ( isnan(humidity) || isnan(temperature) ) {
    Print("Error, tidak dapat membaca nilai sensor.");
  }

  delay(3000);
}
