#include <WiFi.h>
#define PORT 8080
#define LED_BUILTIN 2
#define INFRA_SENSOR 4
#define LDR_SENSOR 34
#define TOUCH_SENSOR 14

const char *SSID = "DIGI-X_LOUNGE";
const char *PASSWORD = "IT Certified";

String header= "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
String tailer= "</body></html>";

WiFiServer server(PORT);
WiFiClient client;

long randomnumber;
String s;
String cmd;

void setup() {
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.print("Web Server active: ");
  Serial.println( WiFi.localIP() );
  server.begin();
  randomSeed(42);

  pinMode(INFRA_SENSOR, INPUT);
  pinMode(LDR_SENSOR, INPUT);
  pinMode(TOUCH_SENSOR, INPUT);
}

void loop() {
  client= server.available(); //tunggu client
  //Serial.println("waiting for client ");
  if (client) { // dapat client baru
    Serial.println("got a new client");
    while (client.connected() ) {
      if ( client.available()) {
      //Serial.println("Data can be read");
      s = client.readString();
      cmd= getCommand(s);
        if (cmd.equals("")) {
          refresh(0, 0, 0);
        } else if(cmd.equals("refresh?")) {
          refresh(readSensorInfra(), readLdrSensor(), readTouchSensor()); // min max
        } else {
          refresh(0, 0, 0);
          client.stop();
        }
        Serial.println(cmd);
        delay(100);
      }
      else {
        client.stop();
      }
    }
    //client.stop();
  }
  else {
  //Serial.println("No client yet ");
  }
  delay(1000);
}

void refresh (int nilai, int nilai2, int nilai3) {
  client.println(header);
  client.print ("<html><head><title>Sensor</title>");
  client.print ("<meta name='viewport' content='width=device-width,initial-scale=1.0'>");
  client.print ("</head>");
  client.print ("<body><h1>Data Sensor</h1>");
  client.printf("<p>Nilai Data Dari Sensor Infrared adalah : %d </p>", nilai);
  client.printf("<p>Nilai Data Dari Sensor LDR adalah : %d </p>", nilai2);
  client.printf("<p>Nilai Data Dari Sensor Touch adalah : %d </p>", nilai3);
  client.print ("<p><form action='/refresh'><input type='submit'value='Refresh'></p>");
  client.println(tailer);
}

String getCommand(String s) {
  int i;
  i= s.indexOf(' ',5);
  return (s.substring(5, i));
}

int readSensorInfra () {
  int value = digitalRead(INFRA_SENSOR);
  Serial.print("Infrared sensor: ");
  Serial.print(value);
  Serial.println();
  return value;
}

int readLdrSensor () {
  int value = analogRead(LDR_SENSOR);
  Serial.print("LDR Sensor: ");
  Serial.print(value);
  Serial.println();
  return value;
}

int readTouchSensor () {
  int value = touchRead(TOUCH_SENSOR);
  Serial.print("Touch Sensor: ");
  Serial.print(value);
  Serial.println();
  return value;
}
