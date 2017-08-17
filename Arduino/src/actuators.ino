#include <Atlasbuggy.h>
#include <Motors.h>
#include <PanTiltController.h>

// LEFT MOTOR PINS
int enA = 10;
int in1 = 9;
int in2 = 8;
// RIGHT MOTOR PINS
int enB = 11;
int in3 = 7;
int in4 = 6;
// SERVO PINS
int pan_pin = A0;
int tilt_pin = A1;

int left_pins[3] = {in1, in2, enA};
int right_pins[3] = {in3, in4, enB};

Atlasbuggy robot("actuators");
Motors wheel_actuators(left_pins, right_pins);
PanTiltController camera_servos(pan_pin, tilt_pin);

uint32_t timer = millis();

void setup()
{
 // initialize robot and wheel actuators
 wheel_actuators.begin();
 robot.begin();
 camera_servos.begin();
}

void loop()
{
  // if (!robot.isPaused()){
  //   if (timer > millis())  timer = millis();  // reset the timer if there is overflow
  //     // if ((millis() - timer) > 500) {  // every 0.5 seconds, print the current time in milliseconds
  //     //   Serial.print(millis());
  //     //   Serial.print('\n');
  //     // }
  // }

  while (robot.available()){
    int status = robot.readSerial();
    if (status == 0){
      String command = robot.getCommand();
      Serial.print(command);
      Serial.print('\n');
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
          camera_servos.tilt_up();
        }
        else if (command.charAt(1) == 'd'){
          camera_servos.tilt_down();
        }
        else if (command.charAt(1) == 'l'){
          camera_servos.pan_left();
        }
        else if (command.charAt(1) == 'r'){
          camera_servos.pan_right();
        }
        else if (command.charAt(1) == 'c'){
          camera_servos.pan_center();
        }
        camera_servos.detach_servos();
      }
    }
  }
}
