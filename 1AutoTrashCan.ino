#include <Servo.h>

// --- Pins ---
const int SERVO1_PIN = 9;   // Lid Servo
const int SERVO2_PIN = 3;   // Extra Servo
const int TRIG_PIN = 10;
const int ECHO_PIN = 11;

Servo servo1;
Servo servo2;

// --- Range Settings ---
const int OPEN_THRESHOLD = 100;
const int CLOSE_THRESHOLD = 150;

// --- State Variables ---
bool lidState = false;

// --- Speed Settings ---
const int SPEED_STEP = 2;
const int SPEED_DELAY = 15;

void setup() {
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  
  // Start positions (Both at 0)
  servo1.write(0); 
  servo2.write(0);
  
  Serial.begin(9600);
  Serial.println("Reversed Lid Ready.");
}

void loop() {
  int distance = getAverageDistance();
  
  // 1. If Close AND Lid is Closed -> OPEN
  if (distance < OPEN_THRESHOLD && !lidState) {
    openLidReversed();
    lidState = true;
  }
  // 2. If Far AND Lid is Open -> CLOSE
  else if (distance > CLOSE_THRESHOLD && lidState) {
    closeLidReversed();
    lidState = false;
  }
  
  delay(100);
}

// --- Reversed Open: Servo1 DOWN (90->0), Servo2 UP (0->90) ---
void openLidReversed() {
  int target1 = 0;   // Servo 1 goes Down
  int target2 = 90;  // Servo 2 goes Up
  
  while (servo1.read() != target1 || servo2.read() != target2) {
    if (servo1.read() > target1) servo1.write(servo1.read() - SPEED_STEP);
    if (servo2.read() < target2) servo2.write(servo2.read() + SPEED_STEP);
    delay(SPEED_DELAY);
  }
  Serial.println("--- LID OPENED (Reversed) ---");
}

// --- Reversed Close: Servo1 UP (0->90), Servo2 DOWN (90->0) ---
void closeLidReversed() {
  int target1 = 90;  // Servo 1 goes Up
  int target2 = 0;   // Servo 2 goes Down
  
  while (servo1.read() != target1 || servo2.read() != target2) {
    if (servo1.read() < target1) servo1.write(servo1.read() + SPEED_STEP);
    if (servo2.read() > target2) servo2.write(servo2.read() - SPEED_STEP);
    delay(SPEED_DELAY);
  }
  Serial.println("--- LID CLOSED (Reversed) ---");
}

int getAverageDistance() {
  int sum = 0;
  for(int i = 0; i < 5; i++) {
    sum += getDistance();
    delay(10);
  }
  return sum / 5;
}

int getDistance() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH, 50000);
  if (duration == 0) return -1;
  return duration * 0.034 / 2;
}