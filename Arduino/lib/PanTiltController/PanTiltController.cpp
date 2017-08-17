#include <PanTiltController.h>

PanTiltController::PanTiltController(int pan_pin, int tilt_pin)
{
  _pan_pin = pan_pin;
  _tilt_pin = tilt_pin;
  _attached = 0;
  Servo pan_servo;
  Servo tilt_servo;
  _pan_servo = pan_servo;
  _tilt_servo = tilt_servo;
  _servo_pos[0] = 90;
  _servo_pos[1] = 90;
}

void PanTiltController::begin(){
  attach_pan();
  _pan_servo.write(_servo_pos[0]);
  delay(DELAY_TIME);
  attach_tilt();
  _tilt_servo.write(_servo_pos[1]);
  delay(DELAY_TIME);
  detach_servos();
}

void PanTiltController::pan_center(){
  // pan Servo
  if (_attached != -1)
    attach_pan();

  _servo_pos[0] = 90;
  _pan_servo.write(90);
  delay(100);
  detach_servos();
}

void PanTiltController::pan_left()
{
  // pan servo
  if (_attached != -1){
    attach_pan();
  }
  int pos = _servo_pos[0];
  pos += 10;
  if (pos > SERVO_MAX){
    pos = SERVO_MAX;
  }
  _servo_pos[0] = pos;
  _pan_servo.write(pos);
  delay(DELAY_TIME);
  detach_servos();
}

void PanTiltController::pan_right()
{
  // pan servo
  if (_attached != -1){
    attach_pan();
  }
  int pos = _servo_pos[0];
  pos -= 10;
  if (pos < SERVO_MIN){
    pos = SERVO_MIN;
  }
  _servo_pos[0] = pos;
  _pan_servo.write(pos);
  delay(DELAY_TIME);
  detach_servos();
}

void PanTiltController::tilt_down()
{
  // tilt servo
  if (_attached != 1){
    attach_tilt();
  }
  int pos = _servo_pos[1];
  pos += 10;
  if (pos > SERVO_MAX){
    pos = SERVO_MAX;
  }
  _servo_pos[1] = pos;
  _tilt_servo.write(pos);
  delay(DELAY_TIME);
  detach_servos();
}

void PanTiltController::tilt_up()
{
  // tilt servo
  if (_attached != 1){
    attach_tilt();
  }

  int pos = _servo_pos[1];
  pos -= 10;
  if (pos < SERVO_MIN){
    pos = SERVO_MIN;
  }
  _servo_pos[1] = pos;
  _tilt_servo.write(pos);
  delay(DELAY_TIME);
  detach_servos();
}

void PanTiltController::attach_pan()
{
  if (_attached == 1){
    detach_servos();
  }
  _pan_servo.attach(_pan_pin);
  delay(20);
  _attached = -1;
}

void PanTiltController::attach_tilt()
{
  if (_attached == -1){
    detach_servos();
  }
  _tilt_servo.attach(_tilt_pin);
  delay(20);
  _attached = 1;
}

void PanTiltController::detach_servos()
{
  if (_attached == -1){
    _pan_servo.detach();
  }
  else if (_attached == 1){
    _tilt_servo.detach();
  }
  _attached = 0;
}
