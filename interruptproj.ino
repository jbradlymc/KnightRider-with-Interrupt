const int ledPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int buttonPins[] = {A0, A1, A2, A3, A4, A5};

volatile int currentPattern = -1; 
unsigned long previousMillis = 0;  
const int interval = 100;          

unsigned long lastPressTime[6] = {0, 0, 0, 0, 0, 0};
const unsigned long debounceDelay = 50; 

int krIndex = 0;
int krDirection = 1;

void setup() {
  for (int i = 0; i < 8; i++) pinMode(ledPins[i], OUTPUT);
  for (int i = 0; i < 6; i++) pinMode(buttonPins[i], INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      if (millis() - lastPressTime[i] > debounceDelay) {
        currentPattern = i;
        Serial.print("Pattern selected: ");
        Serial.println(i + 1);
        clearLEDs();
        lastPressTime[i] = millis();
      }
    }
  }

  switch (currentPattern) {
    case 0: pattern1(); break;
    case 1: pattern2(); break;
    case 2: pattern3(); break;
    case 3: pattern4(); break;
    case 4: pattern5(); break;
    case 5: pattern6(); break;
  }
}

void pattern1() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    clearLEDs();
    digitalWrite(ledPins[krIndex], HIGH);
    krIndex += krDirection;
    if (krIndex >= 7 || krIndex <= 0) krDirection *= -1;
  }
}

void pattern2() {
  unsigned long currentMillis = millis();
  static int step = 0;
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    clearLEDs();
    int c1 = 3 - step;
    int c2 = 4 + step;
    digitalWrite(ledPins[c1], HIGH);
    digitalWrite(ledPins[c2], HIGH);
    step++;
    if (step > 3) step = 0;
  }
}

void pattern3() {
  unsigned long currentMillis = millis();
  static int step = 0;
  static int direction = 1;
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    clearLEDs();
    digitalWrite(ledPins[step], HIGH);
    digitalWrite(ledPins[step + 1], HIGH);
    step += direction;
    if (step >= 6) direction = -1;
    if (step <= 0) direction = 1;
  }
}

void pattern4() {
  unsigned long currentMillis = millis();
  static int step = 0;
  if (currentMillis - previousMillis >= 100) {
    previousMillis = currentMillis;
    clearLEDs();
    digitalWrite(ledPins[step], HIGH);
    step++;
    if (step >= 8) step = 0;
  }
}

void pattern5() {
  unsigned long currentMillis = millis();
  static int step = 0;
  if (currentMillis - previousMillis >= 200) {
    previousMillis = currentMillis;
    clearLEDs();
    digitalWrite(ledPins[step], HIGH);
    digitalWrite(ledPins[7 - step], HIGH);
    step++;
    if (step > 3) step = 0;
  }
}

void pattern6() {
  unsigned long currentMillis = millis();
  static bool state = false;
  static int count = 0;
  if (currentMillis - previousMillis >= 200) {
    previousMillis = currentMillis;
    state = !state;
    for (int i = 0; i < 8; i++) digitalWrite(ledPins[i], state ? HIGH : LOW);
    if (state) count++;
    if (count >= 3) count = 0; 
  }
}

void clearLEDs() {
  for (int i = 0; i < 8; i++) digitalWrite(ledPins[i], LOW);
}
