#include <Wire.h>
void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Wire.begin(4);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  char tf = Wire.read();    // receive byte as an integer
  if (tf == 't') {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);

  }
  else if (tf == 'f') {
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
  }
}
void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
