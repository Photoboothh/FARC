#include <PS2X_lib.h>

#define PS2_DAT 12 // MISO 
#define PS2_CMD 13 // MOSI 
#define PS2_SEL 15 // SS 
#define PS2_CLK 14 // SLK

#define HIGH_SPEED 2048
#define NOR_SPEED 1500

int timer;
bool hold = 0;

PS2X ps2x;

void setupController() {
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}

int speed = NOR_SPEED;
void Controldrivetrain() {
  if (ps2x.ButtonPressed(PSB_SELECT)) {
    if (speed == NOR_SPEED) {
      speed = HIGH_SPEED;
    }
    if (speed == HIGH_SPEED) {
      speed = NOR_SPEED;
    }
  }
  int joystick_rx = 127 - ps2x.Analog(PSS_RX);
  int joystick_ly = 128 - ps2x.Analog(PSS_LY);
  int leftmotor = -(joystick_ly + joystick_rx);
  int rightmotor = joystick_ly - joystick_rx;

  int p8=0 ,p9=0, p10=0, p11=0;
  
  if (joystick_ly == 0 &&joystick_rx == -1) {
    drivetrain(0,0,0,0);
  }

  if (leftmotor > 0) {
    p8 = leftmotor;
    p8 = map(p8, 0, 128, 0, speed);
  }
  if (leftmotor < 0) {
    p9 = abs(leftmotor);
    p9 = map(p9, 0, 128, 0, speed);
  }
  if (rightmotor > 0) {
    p10 = rightmotor;
    p10 = map(p10, 0, 128, 0, speed);
  }
  if (rightmotor < 0) {
    p11 = abs(rightmotor);
    p11 = map(p11, 0, 128, 0, speed);
  }
  drivetrain(p8,p9,p10,p11);
}

void ControlSlide() {
  int p12=0, p13=0, p14=0, p15=0;
  if (ps2x.ButtonPressed(PSB_R1)) {
    if ( hold == 0 ) {
      hold = 1;
    }
    else {
      hold = 0;
    }
  }
  if ( hold == 1 ) {
    p12=200, p15=200;
  }
  if (ps2x.Button(PSB_PAD_UP)) {
    timer = 14;
  }
  else if (ps2x.Button(PSB_PAD_DOWN)) {
    p13 = 500;
    p14 = 500;
  }
  else if (ps2x.Button(PSB_L1)) {
    p12 = p15 = 2000;
  }
  slidePower(p12, p13, p14 ,p15); 
}
int servoangle = 170;
int door_pwm = 1500;
bool open = 0;
void ControlServo() {
  if (ps2x.ButtonPressed(PSB_CROSS)) {
    if (servoangle == 30) {
      servoangle = 0;
      servoAngle(servoangle);
    }
    else {
      servoangle = 30;
      servoAngle(servoangle);
    }
  }
  if (ps2x.Button(PSB_START)) {
    servoAngle(170);
  }
  if (ps2x.ButtonPressed(PSB_R2)) {
    if (open == 0) {
      door_pwm = 1000;
      door(door_pwm);
      delay(100);
      door(1500);
    }
    if (open == 1) {
      door_pwm = 2000;
      door(door_pwm);
      delay(100);
      door(1500);
    }
  }
}
void runn() {
  if ( timer != 0 ) {
    slidePower(3000, 0, 0, 3000);
    timer -= 1;
  }
}