#define RED_RIGHT 2
#define YELLOW_RIGHT 5
#define GREEN_RIGHT 19
#define RED_LEFT 23
#define YELLOW_LEFT 22
#define GREEN_LEFT 21
#define DELAY_3S 3000
#define DELAY_1S 1000
#define DELAY_2S 2000
#define DELAY_7S 7000

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
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(tg1, OUTPUT);
  pinMode(ech1, INPUT);
  pinMode(RED_RIGHT, OUTPUT);
  pinMode(YELLOW_RIGHT, OUTPUT);
  pinMode(GREEN_RIGHT, OUTPUT);
  pinMode(RED_LEFT, OUTPUT);
  pinMode(YELLOW_LEFT, OUTPUT);
  pinMode(GREEN_LEFT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int delayUltra;
  
  jarak = cek_sensor(tg1, ech1);
  delay(2000);

  if (jarak >= 5 && jarak <= 20) {
    delayUltra = DELAY_7S;
  } else {
    delayUltra = DELAY_3S;
  }
  
  digitalWrite(GREEN_RIGHT, HIGH);
  digitalWrite(RED_LEFT, HIGH);
  digitalWrite(YELLOW_LEFT, LOW);
  digitalWrite(RED_RIGHT, LOW);
  delay(delayUltra);

  digitalWrite(GREEN_RIGHT, LOW);
  digitalWrite(YELLOW_RIGHT, HIGH);
  delay(DELAY_1S);

  digitalWrite(YELLOW_RIGHT, LOW);
  digitalWrite(RED_LEFT, LOW);
  digitalWrite(RED_RIGHT, HIGH);
  digitalWrite(GREEN_LEFT, HIGH);
  delay(DELAY_3S);

  digitalWrite(GREEN_LEFT, LOW);
  digitalWrite(YELLOW_LEFT, HIGH);
  delay(DELAY_1S);
}
