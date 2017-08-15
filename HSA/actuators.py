from atlasbuggy.serial import SerialObject

class Actuators(SerialObject):
    def __init__(self):
        super(Actuators, self).__init__('actuators')

    def camera_up(self):
        print("CAMERA UP BOSS")
        self.send('cu')

    def camera_down(self):
        print("CAMERA DOWN BOSS")
        self.send('cd')

    def camera_left(self):
        print("CAMERA LEFT BOSS")
        self.send('cl')

    def camera_right(self):
        print("CAMERA RIGHT BOSS")
        self.send('cr')

    def robot_forward(self):
        self.send('rf')

    def robot_backward(self):
        self.send('rb')

    def robot_left(self):
        self.send('rl')

    def robot_right(self):
        self.send('rr')
