#include <Wire.h>
/* SDA/SCL ->45번핀 할당되어있음
   릴레이 핀 1,2,7,8 127->드라이 8->바스
   pwm핀 3,6,9,10,11 3,6/9,10 = 드1세기,온도/드2세기,온도 11->바스세기

*/

#define dryer1_power_pin 1
#define dryer2_power_pin 2
#define dryer3_power_pin 7
#define bath_power_pin 8

#define dryer1_intensity_pin 3
#define dryer1_temperature_pin 6
#define dryer2_intensity_pin 9
#define dryer2_temperature_pin 10
#define bath_intensity_pin 11
int dryer_on=0;
int bath_on=0;
int dryer_state[3][3] = {{0, 0, 0},{0, 0, 0}}; //power,intensity,temp
int bath_state=0;
int slave_addr[2] = {0x04, 0x05}; //드라이/욕조 i2c 주소
int device_code=0; //1 for dryer, 2 for bath
void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  Wire.requestFrom(slave_addr[0], 8);    // request 7 bytes from slave device 0x04
  i2c_decoder(0);
  Wire.requestFrom(slave_addr[1], 3);    // request 3 bytes from slave device 0x05
  i2c_decoder(1);
}

void i2c_decoder(int i){


  while (Wire.available()) { // slave may send less than requested
    if (device_code==0){//첫 코드 읽기
      device_code=Wire.read();
    }
    if (device_code==1){//코드가 드라이어 코드이면
      dryer_on==Wire.read();//결제여부
      for(int i=0; i<2;i++){//드라이어 1,2
        for(int j=0; j<3;j++){//일시정지/강도/온도
          dryer_state[i][j]=Wire.read();
        }
      }
    }
    else if(device_code==2){//코드가 배스 코드이면
      bath_on=Wire.read();//일시정지 여부
      bath_state=Wire.read();//세기
    }
  }
}
