#include <Motors.h>
#include <Arduino.h>

Motors::Motors(int left_pins[], int right_pins[])
{
  // left_pins: in1, in2, enA
  // right_pins: in3, in4, enB
  _left_pins = left_pins;
  _right_pins = right_pins;
}

Motors::begin()
{
  // initialize pins as output
  for(int i = 0; i < 3; i++){
    pinMode(_left_pins[i], OUTPUT);
    pinMode(_right_pins[i], OUTPUT);
  }
}

Motors::_leftMotorForward(int power)
{
  // this function makes the left motor go forward
  // set left motor to forward
  digitalWrite(_left_pins[0], HIGH);
  digitalWrite(_left_pins[1], LOW);
  // set left motor speed in range 0~255
  analogWrite(_left_pins[2], power);
}

Motors::_leftMotorBackward(int power)
{
  // this function makes the left motor go backward
  // set left motor to backward
  digitalWrite(_left_pins[0], LOW);
  digitalWrite(_left_pins[1], HIGH);
  // set left motor speed in range 0~255
  analogWrite(_left_pins[2], power);
}

Motors::_leftMotorStop()
{
  // this function stops the left motor
  digitalWrite(_left_pins[0], LOW);
  digitalWrite(_left_pins[1], LOW);
}

Motors::_rightMotorForward(int power)
{
  // this function makes the right motor go forward
  // set right motor to forward
  digitalWrite(_right_pins[0], HIGH);
  digitalWrite(_right_pins[1], LOW);
  // set right motor speed in range 0~255
  analogWrite(_right_pins[2], power);
}

Motors::_rightMotorBackward(int power)
{
  // this function makes the right motor go backward
  // set right motor to backward
  digitalWrite(_right_pins[0], LOW);
  digitalWrite(_right_pins[1], HIGH);
  // set right  motor speed in range 0~255
  analogWrite(_right_pins[2], power);
}

Motors::_rightMotorStop()
{
  // this function makes the right motor stop
  digitalWrite(_right_pins[0], LOW);
  digitalWrite(_right_pins[1], LOW);
}

Motors::robotForward(int power)
{
  // this function makes the robot move forward
  _leftMotorForward(power);
  _rightMotorForward(power);
}

Motors::robotBackward(int power)
{
  // this function makes the robot move backward
  _leftMotorBackward(power);
  _rightMotorBackward(power);

}

Motors::robotStop(int left_power, int right_power)
{
  while(left_power > 0 || right_power > 0){
    if (left_power > 0){
      left_power--;
    }
    if (right_power > 0){
      left_power--;
    }
    analogWrite(enA, left_speed);
    analogWrite(enB, right_speed);
    delay(200);
  }
}

Motors::forward_backward_demo()
{
  robotForward(200);
  delay(1000);
  robotStop(200, 200);
  delay(1000);
  robotBackward(200);
  delay(1000);
}

Motors::move_forward()
{
  robotForward(200);
  delay(500);
  robotStop(200, 200);
  delay(500);
}

Motors::move_backward()
{
  robotBackward(200);
  delay(500);
  robotStop(200, 200);
  delay(500);
}

Motors::move_left()
{
  delay(500);
}

Motors::move_right()
{
  delay(500);
}
