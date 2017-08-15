from atlasbuggy import AsyncStream

class HSABroadcast(AsyncStream):
    def __init__(self, HSAWebSocket):
        super(HSABroadcast, self).__init__()
        self.websocket_server = HSAWebSocket.websocket_server
        self.converter = HSAWebSocket.output.converter

    async def run(self):
        try:
            while True:
                buf = self.converter.stdout.read(512)
                if buf:
                    self.websocket_server.manager.broadcast(buf, binary=True)
                elif self.converter.poll() is not None:
                    break
        finally:
            self.converter.stdout.close()
