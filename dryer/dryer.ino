#include <Wire.h>
#define raspi_pin 2
const int led_pin[2][2][3] = {{{22, 24, 26}, {28, 30, 32}}, {{23, 25, 27}, {29, 31, 33}}}; //드라이어1,2/세기,온도/123단계
const int button_pin[6] = {42, 44, 46, 48, 50, 52};//버튼 핀들, 풀업필요
const int moduler[6] = {2, 4, 4, 2, 4, 4};//0->1->0 위함(최댓값 나누기)
int state[6];//기본값
const int preset[6] = {1, 1, 1, 1, 1, 1};//드라이어1일시정지 세기 온도 드라이어2일시정지 세기 온도
const int off[6] = {0, 0, 0, 0, 0, 0};
int last_payment = 0; //지난 시각 결제 안됌
int payment; //현재 결제 상태
void setup() {
  memcpy(&state, &off, sizeof(off));//우선 off 상태로 설정
  for (int i = 0; i < 2; i++) { //LED 핀설정
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 3; k++) {
        pinMode(led_pin[i][j][k], OUTPUT);//드라이어 i의, j(세기 혹은 온도)를 위한 k번째 led
      }
    }
  }
  for (int i = 0; i < 6; i++) { //버튼 핀설정 인풋
    pinMode(button_pin[6], INPUT);
  }

  Wire.begin(4);                //i2c설정
  Wire.onRequest(requestEvent); //i2c를 위한 requestEvent 등록
  Serial.begin(9600);

}

void loop() {
  payment = digitalRead(raspi_pin); //라즈베리파이에서 결제되었는가 확인
  if (last_payment == 0 && payment == 1) {//지난번에 안결제, 지금은 결제 ->프리셋 불러와야죠?
    memcpy(&state, &preset, sizeof(state));//현재상태에 프리셋 복사
  }
  else if (last_payment == 1 && payment == 0) {//지난번에 결제, 지금은 안결제 ->꺼야죠?
    memcpy(&state, &off, sizeof(off));//현재상태에 off복사
  }
  last_payment = payment;//지금결제가 다음루프에선 지난결제가 되도록
  if (payment == 1) {//결제한 상태에서만 버튼이 눌리도록합니다.
    for (int i = 0; i < 6; i++) {
      if (digitalRead(button_pin[i]) == LOW) {//버튼눌리면
        state[i] += 1;//1을더하고
        state[i] %= moduler[i];//값의 범위를 넘어가면 0으로 초기화합니다.
      }
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
  Serial.println("");
  delay(100);
}

void requestEvent() {
  Wire.write(1); // dryer code : 1 을 앞에 붙이고
  for (int i = 0; i < 6; i++) {
    Wire.write(state[i]);//요청시 스테이트를 보냅니다
  }
}
