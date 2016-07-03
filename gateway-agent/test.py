import socket
import threading

def server_cccc():
    sss.accept()

sss = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sss.bind(('127.0.0.1', 2020))
sss.listen(1)
t = threading.Thread(target=server_cccc)
t.setDaemon(True)
t.start()
print "stop"
sss.close()
print "stopped"
