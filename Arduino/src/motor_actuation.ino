#include <Atlasbuggy.h>
#include <Motors.h>
#include <Servo.h>
#include <PanTiltController.h>

// LEFT PINS
int enA = 10;
int in1 = 9;
int in2 = 8;
// RIGHT PINS
int enB = 11;
int in3 = 7;
int in4 = 6;
// SERVO PINS
int pan_pin = 4;
int tilt_pin = 5;

int left_pins[3] = {in1, in2, enA};
int right_pins[3] = {in3, in4, enB};

int servo_pos[2] = {90, 90}

Atlasbuggy robot("actuators");
Motors wheel_actuators(left_pins, right_pins);
Servo pan_servo;
Servo tilt_servo;

void incr_servo(bool servo)
{
  int pin;
  if (!servo){
    // pan servo
    pin = pan_pin;
    pos = servo_pos[0];
    pos += 5;
    if (pos > 180){
      pos = 180;
    }
    pan_servo.write(pos);
  }
  else{
    // tilt servo
    pin = tilt_pin;
    pos = servo_pos[1];
    pos += 5;
    if (pos > 180){
      pos = 180);
    }
    tilt_servo.write(pos);
  }
}

void decr_servo(bool servo)
{
  int pin;
  if (!servo){
    // pan servo
    pin = pan_pin;
    pos = servo_pos[0];
    pos -= 5;
    if (pos < 0){
      pos = 0;
    }
    pan_servo.write(pos);
  }
  else{
    // tilt servo
    pin = tilt_pin;
    pos = servo_pos[1];
    pos -= 5;
    if (pos < 0){
      pos = 0);
    }
    tilt_servo.write(pos);
  }
}

void setup()
{
 robot.begin();
 wheel_actuators.begin();
 // initilaize servos
 pan_servo.attach(pan_pin);
 tilt_servo.attach(tilt_pin);
 // center servos
 pan_servo.write(90);
 tilt_servo.write(90);
 delay(15);
}

void loop()
{
  while (robot.available()){
    int status = robot.readSerial();
    if (status == 0){
      command = robot.getCommand();
      if (command.charAt(0) == 'r'){
        if (command.charAt(1) == 'f'){
          wheel_actuators.move_forward();
        }
        else if (command.charAt(1) == 'b'){
          wheel_actuators.move_backward();
        }
        else if (command.charAt(1) == 'l'){
          wheel_actuators.turn_left();
        }
        else if (command.charAt(1) == 'r'){
          wheel_actuators.turn_right();
        }
      }

      else if (command.charAt(0) == 'c'){
        if (command.charAt(1) == 'u'){
          incr_servo(true);
        }
        else if (command.charAt(1) == 'd'){
          decr_servo(true);
        }
        else if (command.charAt(1) == 'l'){
          incr_servo(false);
        }
        else if (command.charAt(1) == 'r'){
          decr_servo(false);
        }
      }
    }
  }
  wheel_actuators.forward_backward_demo();
  delay(1000);
}
