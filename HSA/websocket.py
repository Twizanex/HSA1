import picamera
import io
import os
from time import sleep
from struct import Struct
from subprocess import Popen, PIPE
from wsgiref.simple_server import make_server
from ws4py.websocket import WebSocket
from ws4py.server.wsgirefserver import WSGIServer, WebSocketWSGIRequestHandler
from ws4py.server.wsgiutils import WebSocketWSGIApplication

from atlasbuggy import ThreadedStream

#####################################
# CONFIGURATION
WIDTH = 384
HEIGHT = 288
FRAMERATE = 24
HTTP_PORT = 8082
WS_PORT = 8084
COLOR = u'#444'
BGCOLOR = u'#333'
JSMPEG_MAGIC = b'jsmp'
JSMPEG_HEADER = Struct('>4sHH')
#####################################

class HSAWebSocket(ThreadedStream):
    def __init__(self):
        self.camera = picamera.PiCamera()
        self.camera.resolution = (WIDTH, HEIGHT)
        self.camera.framerate = FRAMERATE
        super(HSAWebSocket, self).__init__()

        print("Initializing Websocket on some port")
        self.websocket_server = make_server(
            '', WS_PORT,
            server_class=WSGIServer,
            handler_class=WebSocketWSGIRequestHandler,
            app=WebSocketWSGIApplication(handler_cls=StreamingWebSocket)
        )
        self.websocket_server.initialize_websockets_manager()
        self.output = BroadcastOutput(self.camera)
        self.camera.start_recording(self.output, 'yuv')
        sleep(1)

    def run(self):
        print("running websocket server FOREVER") 
        self.websocket_server.serve_forever()

    def stop(self):
        self.camera.stop_recording()
        self.camera.close()

class StreamingWebSocket(WebSocket):
    def opened(self):
        self.send(JSMPEG_HEADER.pack(JSMPEG_MAGIC, WIDTH, HEIGHT))

class BroadcastOutput(object):
    def __init__(self, camera):
        print('Spawning background conversion process')
        self.converter = Popen([
            'avconv',
            '-f', 'rawvideo',
            '-pix_fmt', 'yuv420p',
            '-s', '%dx%d' % camera.resolution,
            '-r', str(float(camera.framerate)),
            '-i', '-',
            '-f', 'mpeg1video',
            '-b', '800k',
            '-r', str(float(camera.framerate)),
            '-'],
            stdin=PIPE, stdout=PIPE, stderr=io.open(os.devnull, 'wb'),
            shell=False, close_fds=True)

    def write(self, b):
        self.converter.stdin.write(b)

    def flush(self):
        print('Waiting for background conversion process to exit')
        self.converter.stdin.close()
        self.converter.wait()
