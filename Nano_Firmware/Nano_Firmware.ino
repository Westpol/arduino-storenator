void setup() {
  pinMode(12, OUTPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(12, HIGH);
  for(int i = 0; i < 100; i++){
    digitalWrite(A4, HIGH);
    delay(100);
    digitalWrite(A4, LOW);
    delay(100);
  }
  delay(10000);
  digitalWrite(12, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}
