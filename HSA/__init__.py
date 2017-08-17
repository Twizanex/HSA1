from .actuators import Actuators
from .http_server import HSAServer
from .broadcast import HSABroadcast
from .websocket import HSAWebSocket

import time

from atlasbuggy.subscriptions import Feed
from atlasbuggy.serial import SerialStream

class SecurityBot(SerialStream):
    def __init__(self):
        self.actuators = Actuators()
        super(SecurityBot, self).__init__(self.actuators)

        self.server_tag = 'server'
        self.server_feed = None
        self.require_subscription(self.server_tag, Feed, HSAServer)
        self.pipeline_results = None

    def take(self, subscriptions):
        self.server_feed = subscriptions[self.server_tag].get_feed()

    async def update(self):
        # Ben - this is your issue. SerialStream is an asynchronous stream
        # self.server_feed.get() is a coroutine and won't return a message
        # you'll need to move this stuff into self.update() and call await self.server_feed.get()

        while self.is_running:
            if not self.server_feed.empty():
                #print("running")
                #self.pipeline_results = await self.server_feed.get()
                #message = self.pipeline_results
                message = await self.server_feed.get()
                #print("IT IS BEING CALLED HERE")
                if message == 'forward':
                    self.actuators.robot_forward()
                elif message == 'backward':
                    self.actuators.robot_backward()
                elif message == 'turn-left':
                    self.actuators.robot_left()
                elif message == 'turn-right':
                    self.actuators.robot_right()
                elif message == 'camera-up':
                    self.actuators.camera_up()
                    print("camera goin up")
                elif message == 'camera-down':
                    self.actuators.camera_down()
                    print("camera goin down")
                elif message == 'camera-left':
                    self.actuators.camera_left()
                    print("camera goin left")
                elif message == 'camera-right':
                    self.actuators.camera_right()
                    print("camera goin right")
                elif message == 'camera-center':
                    self.actuators.camera_center()
                    print("camera centerin")
                self.server_feed.task_done()
        await asyncio.sleep(0.0)

    def serial_update(self):
        while self.is_running():
          if self.pipeline_results is not None:
              print("got a message")
              self.pipeline_results = None
          time.sleep(0.1)  
