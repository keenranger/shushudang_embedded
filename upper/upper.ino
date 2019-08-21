#include <Wire.h>
/* SDA/SCL ->45번핀 할당되어있음
   릴레이 핀 1,2,7,8 127->드라이 8->바스
   pwm핀 3,6,9,10,11 3,6/9,10 = 드1세기,온도/드2세기,온도 11->바스세기

*/

#define dryer1_power_pin 1
#define dryer2_power_pin 2
#define dryer3_power_pin 7
#define bath_power_pin 8'

#define dryer1_intensity_pin 3
#define dryer1_temperature_pin 6
#define dryer2_intensity_pin 9
#define dryer2_temperature_pin 10
#define bath_intensity_pin 11

int dryer1_state[3] = {0, 0, 0}; //power,intensity,temp
int dryer2_state[3] = {0, 0, 0}; //power,intensity,temp
int bath_state[3] = {0, 0, 0};
char raspi_state[2] = {'f', 'f'}; //라즈베리파이 전원 기본상태 = f(꺼짐) //t=켜짐
int raspi_pin[2] = {12, 13}; //라즈베리파이 핀 전원확인 핀
int slave_addr[2] = {0x04, 0x05} //드라이/욕조 i2c 주소
void setup() {
  Wire.begin();
  pinMode(12, INPUT);
  pinMode(13, INPUT);
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 2; i++) { //라즈베리파이로부터 결제되었는지 확인하는 부분
    if (digitalRead(raspi_pin[i]) == HIGH)
      raspi_state[i] = 't';
    else
      raspi_state[i] = 'f';
  }
  for (int i = 0; i < 2; i++) {//결제여부를 밑의 아두이노에게 i2c로 보내는 부분
    Wire.beginTransmission(slave_addr[i]);
    Wire.write(raspi_state[i]);
    Wire.endTransmission();
  }
  if (             d.;A[0] == 't' && 0] == 1) { //드라이어 결제되었고, 드라이어 on이면

  }
}
