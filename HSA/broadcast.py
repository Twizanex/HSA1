import asyncio

from atlasbuggy import ThreadedStream

class HSABroadcast(ThreadedStream):
    def __init__(self, HSAWebSocket):
        super(HSABroadcast, self).__init__()
        self.websocket_server = HSAWebSocket.websocket_server
        self.converter = HSAWebSocket.output.converter

    def run(self):
        while self.is_running():
            buf = self.converter.stdout.read(512)
            if buf:
                self.websocket_server.manager.broadcast(buf, binary=True)
            elif self.converter.poll() is not None:
                break

    def stop(self):
        self.converter.stdout.close()
