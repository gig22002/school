from socket import *
from Cryptodome.PublicKey import RSA

#cryptography
path = input("Input private key path: ")
pwd = input("Password: ")
with open(path, "rb") as f:
    data = f.read()
    sk = RSA.import_key(data, pwd.encode())
print(sk)

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
