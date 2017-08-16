from atlasbuggy.serial import SerialStream, SerialObject

# Ben - I recommend just moving this to the HSA module since this is the only file in this module
class Actuators(SerialObject):
    def __init__(self):
        super(Actuators, self).__init__('actuators')

    def receive_first(self, packet):
        pass

    def receive(self, timestamp, packet):
        pass

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

class SecurityBot(SerialStream):
    def __init__(self):
        self.actuators = Actuators()
        super(SecurityBot, self).__init__(self.actuators)
