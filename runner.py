from atlasbuggy import Robot
from HSA import SecurityBot, HSAServer, HSAWebSocket, HSABroadcast

robot = Robot(write=log)

securitybot = SecurityBot()
server = HSAServer()
websocket = HSAWebSocket()
broadcast = HSABroadcast(websocket)

consumer.subscribe(Feed(securitybot.server_tag, server))

robot.run(securitybot, server, websocket, broadcast)
