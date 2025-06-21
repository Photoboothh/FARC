#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void drivetrain(int p8, int p9, int p10, int p11) {
  pwm.setPin (8, p8);
  pwm.setPin (9, p9);
  pwm.setPin (10, p10);
  pwm.setPin (11, p11);
}

void slidePower(int p12, int p13, int p14, int p15) {
  pwm.setPin (12, p12);
  pwm.setPin (13, p13);
  pwm.setPin (14, p14);
  pwm.setPin (15, p15);
}

void servoAngle(int deg) {
  int pwm_value1 = map(deg , 0, 180, 102, 512); 
  pwm.setPWM(7, 0, pwm_value1);
  int pwm_value2 = map(180 - deg , 0, 180, 102, 512); 
  pwm.setPWM(6, 0, pwm_value2);
}
void door(int door_pwm) {
  pwm.setPWM(5, 0, door_pwm);
}
void setupMotors() {
  Wire.begin(); 
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);

  drivetrain(0, 0, 0, 0);
  slidePower (0, 0, 0, 0);
  servoAngle(170);
  
}
