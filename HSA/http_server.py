import io
from time import time, sleep
from string import Template
from http.server import HTTPServer, BaseHTTPRequestHandler

from atlasbuggy import ThreadedStream

###########################################
# CONFIGURATION
WIDTH = 384
HEIGHT = 288
HTTP_PORT = 8082
COLOR = u'#444'
BGCOLOR = u'#333'
###########################################

post_func = None

class HSAServer(ThreadedStream):
    def __init__(self):
        super(HSAServer, self).__init__()
        global post_func
        post_func = self.post
        self.http_server = StreamingHttpServer()

    def run(self):
        print("Starting HTTP Server on port {}".format(HTTP_PORT))
        self.http_server.serve_forever()

class StreamingHttpServer(HTTPServer):
    def __init__(self):
        super(StreamingHttpServer, self).__init__(
                ('', HTTP_PORT), StreamingHttpHandler)
        with io.open('index.html', 'r') as f:
            self.index_template = f.read()
        with io.open('jsmpg.js', 'r') as f:
            self.jsmpg_content = f.read()

class StreamingHttpHandler(BaseHTTPRequestHandler):
    def do_HEAD(self):
        self.do_GET()

    def do_GET(self):
        global post_func
        content_type = 'text/plain'
        content = 'success'
        if self.path == '/':
            self.send_response(301)
            self.send_header('Location', '/index.html')
            self.end_headers()

        elif self.path == '/jsmpg.js':
            content_type = 'application/javascript'
            content = self.server.jsmpg_content

        elif self.path == '/index.html':
            content_type = 'text/html; charset=utf-8'
            tpl = Template(self.server.index_template)
            content = tpl.safe_substitute(dict(
                ADDRESS='%s:%d' % ("' + window.location.hostname +'", WS_PORT),
                WIDTH=WIDTH, HEIGHT=HEIGHT, COLOR=COLOR, BGCOLOR=BGCOLOR))

        elif self.path == '/forward':
            post_func('forward')
            self.send_response(200)
            print('SERVER: moving forward')

        elif self.path == '/backward':
            post_func('backward')
            self.send_response(200)
            print('SERVER: moving backward')

        elif self.path == '/turn-left':
            post_func('turn-left')
            self.send_response(200)
            print('SERVER: turn left')

        elif self.path == '/turn-right':
            post_func('turn-right')
            self.send_response(200)
            print('SERVER: turn right')

        elif self.path == '/camera-up':
            post_func('camera-up')
            self.send_response(200)
            print('SERVER: camera up')

        elif self.path == '/camera-down':
            post_func('camera-down')
            self.send_response(200)
            print('SERVER: camera down')

        elif self.path == '/camera-left':
            post_func('camera-left')
            self.send_response(200)
            print('SERVER: camera left')

        elif self.path == '/camera-right':
            post_func('camera-right')
            self.send_response(200)
            print('SERVER: camera right')

        else:
            self.send_error(404, 'File not found')
            return
        content = content.encode('utf-8')
        self.send_response(200)
        self.send_header('Content-Type', content_type)
        self.send_header('Content-Length', len(content))
        self.send_header('Last-Modified', self.date_time_string(time()))
        self.end_headers()
        if self.command == 'GET':
            self.wfile.write(content)
