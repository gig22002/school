from socket import *
import threading

MSGLEN = 2048

class Sock:
    def __init__(self, sock=None):
        if not sock:
            self.sock = socket(AF_INET, SOCK_STREAM)
        else:
            self.sock = sock

    def connect(self, host, port):
        self.sock.connect((host, port))

    def mysend(self, msg):
        total = 0
        while total < MSGLEN:
            sent = self.sock.send(msg[total:])
            if sent == 0:
                raise RuntimeError("Connection broken")
            total += sent

    def myreceive(self):
        chunks = []
        recvd = 0
        while recvd < MSGLEN:
            chunk = self.sock.recv(min(MSGLEN - recvd, 2048))
            if chunk == b'':
                raise RuntimeError("Connection broken")
            chunks.append(chunk)
            recvd += len(chunk)
        return b''.join(chunks)
            

s = socket(AF_INET, SOCK_STREAM)
s.bind((gethostname(), 25565))
s.listen(5)

while 1:
    (clientsock, addr) = s.accept()

    ct = make_client_thread(clientsock)
    ct.start()
