import socket
import threading

class socket_server:

    _running = False

    def __init__(self, server_port, callback):
        self._server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self._server_sock.bind(('127.0.0.1', server_port))
        self._server_sock.listen(1)
        self._running = True
        self._callback = callback
        self._trd = threading.Thread(target=self._listen)
        self._trd.setDaemon(True)

    def _listen(self):
        while self._running:
            try:
                print "=========="
                sock, addr = self._server_sock.accept()
                bytedata = bytearray(sock.recv(1400))
                print "New configuration message!"
                returnbyte = self._callback(bytedata)
                sock.sendall(returnbyte)
                sock.close()
                print "Result sent!"
            except BaseException, e:
                print e
                break

    def start(self):
        self._trd.start()

    def stop(self):
        self._running = False
        self._server_sock.close()