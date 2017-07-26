// LEFT MOTOR PINS
// HIGH, LOW -> forward
// LOW, HIGH -> backward
// LOW, LOW -> stop
int enA = 10;
int in1 = 9;
int in2 = 8;

// RIGHT MOTOR PINS
// HIGH, LOW -> forward
// LOW, HIGH -> backward
// LOW, LOW -> stop
int enB = 11;
int in3 = 7;
int in4 = 6;

void setup() {
 // set all the motor control pins to outputs
 pinMode(enA, OUTPUT);
 pinMode(enB, OUTPUT);
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
}

void leftMotorForward(int pow) {
  // this function makes the left motor go forward
  // set left motor to forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // set left motor speed in range 0~255
  analogWrite(enA, pow);
}

void leftMotorBackward(int pow) {
  // this function makes the left motor go backward
  // set left motor to backward
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // set left motor speed in range 0~255
  analogWrite(enA, pow);
}

void leftMotorStop() {
  // this function stops the left motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void rightMotorForward(int pow) {
  // this function makes the right motor go forward
  // set right motor to forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // set right motor speed in range 0~255
  analogWrite(enB, pow);
}

void rightMotorBackward(int pow) {
  // this function makes the right motor go backward
  // set right motor to backward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // set right motor speed in range 0~255
  analogWrite(enB, pow);
}

void rightMotorStop() {
  // this function stops the right motor
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void robotForward(int vel) {
  // this function makes the robot move forward
  leftMotorForward(vel);
  rightMotorForward(vel);
}

void robotBackward(int vel) {
  // this function makes the robot move backward
  leftMotorBackward(vel);
  rightMotorBackward(vel);
}

void robotStop() {
  // this function makes the robot stop
  leftMotorStop();
  rightMotorStop();
}

void brake(int left_speed, int right_speed) {
  while(left_speed > 0 && right_speed > 0){
    left_speed = left_speed > 0 ? left_speed - 1 : 0;
    right_speed = right_speed < 0 ? right_speed - 1 : 0;
    analogWrite(enA, left_speed);
    analogWrite(enB, right_speed);
    delay(20);
  }
}

void forward_backward_demo() {
  robotForward(200);
  delay(1000);
  brake(200, 200);
  robotBackward(200);
  delay(1000);
  robotStop();
}

void loop()
{
  forward_backward_demo();
  delay(1000);
}
