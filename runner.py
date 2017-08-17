from atlasbuggy import Robot
from atlasbuggy.subscriptions import Feed
from HSA import SecurityBot, HSAServer, HSAWebSocket 

robot = Robot()

securitybot = SecurityBot()
server = HSAServer()
websocket = HSAWebSocket()

securitybot.subscribe(Feed(securitybot.server_tag, server))

robot.run(securitybot, server, websocket)
