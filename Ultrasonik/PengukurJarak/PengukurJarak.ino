
int tg1 = 13, ech1 = 12;
int jarak;

int cek_sensor(int out, int in) {
  long duration, distance;

  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, HIGH);
  delayMicroseconds(10);
  digitalWrite(out, LOW);

  duration = pulseIn(in, HIGH);
  distance = (duration/2)/29;

  Serial.print("Jarak: ");
  Serial.println(distance);

  return distance;
}

void setup() {
  Serial.begin(115200);
  pinMode(tg1, OUTPUT);
  pinMode(ech1, INPUT);
}

void loop() {
  jarak = cek_sensor(tg1, ech1);
  delay(2000);
}
