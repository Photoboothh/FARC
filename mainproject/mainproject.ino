#include "Motors.h"
#include "Controller.h"
#include <stdio.h>
 
void setup() {
  Serial.begin(115200);
  setupController();
  setupMotors();
}
void loop() {
  //Cập nhật các giá trị của tay điều khiển
  ps2x.read_gamepad(0, 0); // gọi hàm để đọc tay điều khiển 
  Controldrivetrain();
  ControlSlide();
  ControlServo();
  runn();
  delay(50);
}