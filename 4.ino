#define sensorPin A0

bool read = false;
int t = 0;

void setup(){
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 3900;
  TCCR1B = TCCR1B | (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS10);
  TCCR1B = TCCR1B | (1 << CS12);
  TIMSK1 = TIMSK1 | (1 << OCIE1A);
  pinMode(sensorPin, INPUT);
  sei();
}

ISR(TIMER1_COMPA_vect){
  read = true;
}

void loop(){
  if (read){
    int val = analogRead(A0);
    Serial.println(millis() - t);
    Serial.println(val);
    Serial.println();
    t = millis();
    read = false;
  }
}


