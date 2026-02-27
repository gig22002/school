from socket import *

host = 'localhost'
port = 25565

s = socket(AF_INET, SOCK_STREAM)
s.setsockopt(SOL_SOCKET, SO_KEEPALIVE, 1)
s.connect((host, port))

while 1:
    msg = input("Enter message:")
    if not msg:
        s.close()
        break
    s.sendall(msg.encode())

    data = s.recv(1024)
    print('Received',data,'from server')
