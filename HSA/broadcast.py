from atlasbuggy import AsyncStream

class HSABroadcast(AsyncStream):
    def __init__(self, HSAWebSocket):
        super(HSABroadcast, self).__init__()
        self.websocket_server = HSAWebSocket.websocket_server
        self.converter = HSAWebSocket.output.converter

    async def run(self):
        # Ben - run is never awaited. The async will not switch contexts.
        # put a asyncio.sleep(0.0) somewhere (ideally not 0.0 if you know at what rate you're receiving data.
        # Alternatively you just make this a threaded stream.
        try:
            # Ben - use while self.is_running():
            while True:
                buf = self.converter.stdout.read(512)
                if buf:
                    self.websocket_server.manager.broadcast(buf, binary=True)
                elif self.converter.poll() is not None:
                    break
        finally:
            # Ben - this can be put in self.stop. All exceptions are caught by both DataStream and Robot
            self.converter.stdout.close()
