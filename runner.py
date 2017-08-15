from atlasbuggy import Robot
from atlasbuggy.subscriptions import Feed
from HSA import SecurityBot, HSAServer, HSAWebSocket, HSABroadcast

robot = Robot()

securitybot = SecurityBot()
server = HSAServer(securitybot)
websocket = HSAWebSocket()
broadcast = HSABroadcast(websocket)

securitybot.subscribe(Feed(securitybot.server_tag, server))

robot.run(securitybot, server, websocket, broadcast)
