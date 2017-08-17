class Motors {
public:
  Motors(int left_pins[], int right_pins[]);
  void begin();
  void move_forward();
  void move_backward();
  void turn_left();
  void turn_right();
  void robotForward(int power);
  void robotBackward(int power);
  void robotStop();
  // demos
  void forward_backward_demo();

private:
  int _left_pins[3];
  int _right_pins[3];
  void _leftMotorForward(int power);
  void _leftMotorBackward(int power);
  void _leftMotorStop();
  void _rightMotorForward(int power);
  void _rightMotorBackward(int power);
  void _rightMotorStop();
};
