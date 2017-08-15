from atlasbuggy.serial import SerialObject

class Actuators(SerialObject):
    def __init__(self):
        super(Actuators, self).__init__('actuators')

    def camera_up(self):
        self.send('cu')

    def camera_down(self):
        self.send('cd')

    def camera_left(self):
        self.send('cl')

    def camera_right(self):
        self.send('cr')

    def robot_forward(self):
        self.send('rf')

    def robot_backward(self):
        self.send('rb')

    def robot_left(self):
        self.send('rl')

    def robot_right(self):
        self.send('rr')
