#include <DHT.h>

#define PIN_DHT 14
#define DHT_TYPE DHT11

DHT dht(PIN_DHT, DHT_TYPE);

float humidity;
float temperature;
float lastTemperature = 0;
float lastHumidity = 0;
int baris = 0;
int baris1 = 0;
int titik = 0;
void header() {
  Serial.println("Kelembaban\tTemperatur\tTemperatur");
  Serial.println("    %  \t\tCelcius \tFahrenheit");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  Serial.println("Check DHT Sensor");
  header();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  delay(1000);
  float temperature = dht.readTemperature();

  float humidity = dht.readHumidity();
  float fahrenheit = ((9/5) * temperature) + 32;

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor");

    return;
  }

  float hic = dht.computeHeatIndex(temperature, humidity, false);
  
  if (baris1 == 0) {
    header();
    baris1 = 1;
  }
  
  if (baris == 5) {
    header();
    baris = 0;
  }

  if ((lastTemperature == temperature) && (lastHumidity == humidity)) {
    if (titik <= 20) {
      Serial.print(".");
      titik++; 
    }
  } else {
    titik = 0;
    if (titik == 0) {
      Serial.println("");
    }
    Serial.print(humidity);
    Serial.print("\t\t");
    Serial.print(temperature);
    Serial.print("\t\t");
    Serial.print(fahrenheit);
    Serial.println("");
    lastTemperature = 0;
    lastHumidity = 0;
    baris++;
  }
  delay(1000);
  
  lastTemperature = temperature;
  lastHumidity = humidity;
  
}
