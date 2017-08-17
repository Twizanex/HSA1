#include <Arduino.h>
#include <Servo.h>

#define SERVO_MIN 0
#define SERVO_MAX 170
#define DELAY_TIME 30

class PanTiltController {
public:
  PanTiltController(int pan_pin, int tilt_pin);
  void begin();
  void pan_left();
  void pan_right();
  void tilt_up();
  void tilt_down();
  void attach_pan();
  void attach_tilt();
  void detach_servos();
  void pan_center();
private:
  Servo _pan_servo;
  Servo _tilt_servo;
  int _servo_pos[2];
  int _attached; // -1 (pan), 0 (none), 1 (tilt)
  int _pan_pin;
  int _tilt_pin;
};
