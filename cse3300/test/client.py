from socket import *

host = 'localhost'
port = 25565

while 1:
    s = socket(AF_INET, SOCK_STREAM)
    s.setsockopt(SOL_SOCKET, SO_KEEPALIVE, 1)
    s.connect((host, port))

    msg = input("Enter message:")
    if not msg:
        break
    s.sendall(msg.encode())

    data = s.recv(1024)
    print('Received',data,'from server')
    s.close()
