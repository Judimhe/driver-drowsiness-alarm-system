const int PIR_PIN = 2;
const int BUTTON_PIN = 3;
const int SWITCH_PIN = 4;

const int BUZZER_PIN = 8;
const int LED_PIN = 13;

const unsigned long INACTIVE_TIME = 20000;
const unsigned long WARNING_TIME = 10000;

unsigned long lastMotionTime;

bool warningStarted = false;
unsigned long warningStartTime;

bool alarmOn = false;

void setup() {

  pinMode(PIR_PIN, INPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(SWITCH_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  lastMotionTime = millis();
}

void loop() {

  int motion = digitalRead(PIR_PIN);
  int buttonState = digitalRead(BUTTON_PIN);
  int switchState = digitalRead(SWITCH_PIN);

  if (switchState == LOW) {

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);

    return;
  }

  if (motion == HIGH) {

    lastMotionTime = millis();

    warningStarted = false;
    alarmOn = false;

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  if (!warningStarted &&
      millis() - lastMotionTime >= INACTIVE_TIME) {

    warningStarted = true;
    warningStartTime = millis();
  }

  if (warningStarted &&
      millis() - warningStartTime >= WARNING_TIME) {

    alarmOn = true;
  }

  if (buttonState == HIGH) {

    alarmOn = false;
    warningStarted = false;

    lastMotionTime = millis();

    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }

  if (alarmOn) {

    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000);
  }
}
