#include <Motors.h>
#include <Arduino.h>

Motors::Motors(int left_pins[], int right_pins[])
{
  // left_pins: in1, in2, enA
  // right_pins: in3, in4, enB
  for(int i = 0; i < 3; i++){
    _left_pins[i] = left_pins[i];
    _right_pins[i] = right_pins[i];
  }
}

void Motors::begin()
{
  // initialize pins as output
  for(int i = 0; i < 3; i++){
    pinMode(_left_pins[i], OUTPUT);
    pinMode(_right_pins[i], OUTPUT);
  }
}

void Motors::_leftMotorForward(int power)
{
  // this function makes the left motor go forward
  // set left motor to forward
  digitalWrite(_left_pins[0], HIGH);
  digitalWrite(_left_pins[1], LOW);
  // set left motor speed in range 0~255
  analogWrite(_left_pins[2], power);
}

void Motors::_leftMotorBackward(int power)
{
  // this function makes the left motor go backward
  // set left motor to backward
  digitalWrite(_left_pins[0], LOW);
  digitalWrite(_left_pins[1], HIGH);
  // set left motor speed in range 0~255
  analogWrite(_left_pins[2], power);
}

void Motors::_leftMotorStop()
{
  // this function stops the left motor
  digitalWrite(_left_pins[0], LOW);
  digitalWrite(_left_pins[1], LOW);
}

void Motors::_rightMotorForward(int power)
{
  // this function makes the right motor go forward
  // set right motor to forward
  digitalWrite(_right_pins[0], HIGH);
  digitalWrite(_right_pins[1], LOW);
  // set right motor speed in range 0~255
  analogWrite(_right_pins[2], power);
}

void Motors::_rightMotorBackward(int power)
{
  // this function makes the right motor go backward
  // set right motor to backward
  digitalWrite(_right_pins[0], LOW);
  digitalWrite(_right_pins[1], HIGH);
  // set right  motor speed in range 0~255
  analogWrite(_right_pins[2], power);
}

void Motors::_rightMotorStop()
{
  // this function makes the right motor stop
  digitalWrite(_right_pins[0], LOW);
  digitalWrite(_right_pins[1], LOW);
}

void Motors::robotForward(int power)
{
  // this function makes the robot move forward
  _leftMotorForward(power);
  _rightMotorForward(power);
}

void Motors::robotBackward(int power)
{
  // this function makes the robot move backward
  _leftMotorBackward(power);
  _rightMotorBackward(power);

}

void Motors::robotStop(int left_power, int right_power)
{
  while(left_power > 0 || right_power > 0){
    if (left_power > 0){
      left_power--;
    }
    if (right_power > 0){
      right_power--;
    }
    analogWrite(_left_pins[2], left_power);
    analogWrite(_right_pins[2], right_power);
    delay(200);
  }
}

void Motors::forward_backward_demo()
{
  robotForward(200);
  delay(1000);
  robotStop(200, 200);
  delay(1000);
  robotBackward(200);
  delay(1000);
}

void Motors::move_forward()
{
  robotForward(200);
  delay(500);
  robotStop(200, 200);
  delay(500);
}

void Motors::move_backward()
{
  robotBackward(200);
  delay(500);
  robotStop(200, 200);
  delay(500);
}

void Motors::turn_left()
{
  delay(500);
}

void Motors::turn_right()
{
  delay(500);
}
