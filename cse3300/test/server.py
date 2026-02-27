from socket import *

host = "localhost"
port = 25565

s = socket(AF_INET, SOCK_STREAM)
s.setsockopt(SOL_SOCKET, SO_KEEPALIVE, 1)
s.bind((host, port))
s.listen()

while 1:
    conn, addr = s.accept()
    
    print('Server connected to', addr)

    data = conn.recv(1024)
    print('Received',data)
    if not data: 
        break
    msg = 'ACK'
    conn.sendall(msg.encode())
    conn.close()
