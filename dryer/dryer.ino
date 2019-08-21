#include <Wire.h>

const int led_pin[2][2][3] = {{{22, 24, 26}, {28, 30, 32}}, {{23, 25, 27}, {29, 31, 33}}}; //드라이어1,2/세기,온도/123단계
const int button_pin[6] = {42, 44, 46, 48, 50, 52};
const int divider[6] = {2, 4, 4, 2, 4, 4};
int state[6] = {1, 1, 1, 1, 1, 1};//기본값
const int preset[6] = {1, 1, 1, 1, 1, 1};//드라이어1일시정지 세기 온도 드라이어2일시정지 세기 온도
const int off[6] = {0, 0, 0, 0, 0, 0};
int cnt = 0;

void setup() {
  for (int i = 0; i < 2; i++) { //LED 핀설정
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 3; k++) {
        pinMode(led_pin[i][j][k], OUTPUT);//드라이어 i의, j(세기 혹은 온도)를 위한 k번째 led
      }
    }
  }
  for (int i = 0; i < 6; i++) { //버튼 핀설정
    pinMode(button_pin[6], INPUT);
  }

  Wire.begin(4);                //i2c설정
  Wire.onRequest(requestEvent);
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < 6; i++) {
    if (digitalRead(button_pin[i]) == LOW) {
      state[i] += 1;
      state[i] %= divider[i];
    }
  }
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < state[3 * i + j + 1]; k++) {//state까지의 LED키기
        digitalWrite(led_pin[i][j][k], HIGH);
      }
      if (state[3 * i + j + 1] < 3) {
        for (int k = state[3 * i + j + 1]; k < 3; k++) {//state밖의 LED끄기
          digitalWrite(led_pin[i][j][k], LOW);
        }
      }
    }
  }
  for (int i = 0; i < 6; i++) {
    Serial.print(state[i]);
  }
  Serial.println(cnt);
  delay(100);
  cnt++;
}

void requestEvent() {
  Wire.write("hello "); // respond with message of 6 bytes
  // as expected by master
}
