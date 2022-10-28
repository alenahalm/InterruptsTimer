#define ledPin1 3
#define ledPin2 4
#define ledPin3 5

bool state1 = false;
bool state2 = false;
bool state3 = false;

bool blink2 = false;
bool blink3 = false;

void setup(){
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 62500;
  TCCR1B = TCCR1B | (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS12);
  TIMSK1 |= (1 << OCIE1A);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  sei();
}

void loop(){
  digitalWrite(ledPin1, state1);
  digitalWrite(ledPin2, state2);
  digitalWrite(ledPin3, state3);
  if (Serial.available() >= 1){
    int pin = Serial.read();
    if (pin == '2'){
      blink2 = !blink2;
    }
    if (pin == '3'){
      blink3 = !blink3;
    }
  }
}

ISR(TIMER1_COMPA_vect){
  state1 = !state1;
  state2 = blink2?!state2:false;
  state3 = blink3?!state3:false;
}
