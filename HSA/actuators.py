from atlasbuggy.serial import SerialObject

class Actuators(SerialObject):
    def __init__(self, enabled=True):
        super(Actuators, self).__init__('actuators', enabled)
    
    def receive_first(self, packet):
        pass

    def receive(self, timestamp, packet):
        print(packet)

    def camera_up(self):
        print("CAMERA UP BOSS")
        command = "cu"
        self.send("start")
        self.send(command)

    def camera_down(self):
        print("CAMERA DOWN BOSS")
        command = "cd"        
        self.send(command)

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
