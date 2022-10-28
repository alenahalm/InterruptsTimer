long ms_counter = 0;

void setup(){
  Serial.begin(9600);
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 16000;
  TCCR1B = TCCR1B | (1 << WGM12);
  TCCR1B = TCCR1B | (1 << CS10);
  TIMSK1 = TIMSK1 | (1 << OCIE1A);
  sei();
}

void loop(){
  Serial.print("millis: ");
  Serial.print(millis());
  Serial.print(" my millis: ");
  Serial.println(new_millis());
}

ISR(TIMER1_COMPA_vect){
  ms_counter++;
}

long new_millis(){
  return ms_counter;
}
