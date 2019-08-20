//include <wire.h>

void setup() {
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(12) == LOW) {
    Serial.println("12 high!");
  }

  if (digitalRead(13) == LOW) {
    Serial.println("13 high!");
  }

}
