const int pulsePin = 2;
volatile unsigned long pulseStartH = 0;
volatile unsigned long pulseEndH = 0;
volatile unsigned long pulseStartL = 0;
volatile unsigned long pulseEndL = 0;
volatile unsigned long periodH = 0;
volatile unsigned long periodL = 0;
volatile bool pulseDetectedH = false;
volatile bool pulseDetectedL = false;

void setup() {
  Serial.begin(9600);
  pinMode(pulsePin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pulsePin), pulse_isr, CHANGE);
}

void loop() {
  if (pulseDetectedH) {
    Serial.print("high: ");
    Serial.println(periodH);
    pulseDetectedH = false;
  }
    if (pulseDetectedL) {
    Serial.print("low: ");
    Serial.println(periodL);
    pulseDetectedL = false;
  }
}

void pulse_isr() {
  if (digitalRead(pulsePin) == HIGH) {
    pulseStartH = micros();
  } else {
    pulseEndH = micros();
    if (pulseStartH < pulseEndH) { // Защита от переполнения micros()
      periodH = pulseEndH - pulseStartH;
      pulseDetectedH = true;
    }
  }

  if (digitalRead(pulsePin) == LOW) {
    pulseStartL = micros();
  } else {
    pulseEndL = micros();
    if (pulseStartL < pulseEndL) { // Защита от переполнения micros()
      periodL = pulseEndL - pulseStartL;
      pulseDetectedL = true;
    }
  }  

}