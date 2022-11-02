long delayT = 4963;

long desiredSpeed = 0;
long wheelWidth = 205;
long wheelHeightRatio = 55;
long rimSize = 16;
long toothCountPerRotation = 9;

double wheelHeightInMm = 0;
double wheelPerimeter = 0;

double desiredSpeedInMmS = 0;
double teethPerS = 0;
double microsPerTooth = 0;

void calculateSpeed() {
  wheelHeightInMm = (wheelWidth * wheelHeightRatio * 2 / 100) + rimSize * 25.4;
  wheelPerimeter = 3.14159265359 * wheelHeightInMm;
  desiredSpeedInMmS = desiredSpeed * 1000000 / 3600;
  teethPerS = toothCountPerRotation * desiredSpeedInMmS / wheelPerimeter;
  microsPerTooth = 1000000 / (teethPerS * 2);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  Serial.begin(9600);
  calculateSpeed();
}

char incomingByte;

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    int tempData = Serial.parseInt();
    if (tempData > 0) {
      desiredSpeed = tempData;
      Serial.println(desiredSpeed);
      calculateSpeed();
    }
  }
  digitalWrite(2, HIGH);
  delayMicroseconds(microsPerTooth);
  digitalWrite(2, LOW);
  delayMicroseconds(microsPerTooth);
}
