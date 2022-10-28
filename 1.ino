#define ledPin 11

bool state_now = LOW;
bool state_then = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  cli();
  TCCR2A = 0;
  TCCR2B = 0;
  TCCR2B = TCCR2B | (1 << CS10);
  TCCR2B = TCCR2B | (1 << CS12);
  TIMSK2 = (1 << TOIE1);
  sei();
}

void loop() {
  digitalWrite(ledPin, state_now);
  if (state_now != state_then) {
    state_then = state_now;
    Serial.println(millis());
  }
}

ISR(TIMER2_OVF_vect) {
  state_now = !state_now;
}
