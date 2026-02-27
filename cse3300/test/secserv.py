from socket import *
from Cryptodome.PublicKey import RSA
from Cryptodome.Cipher import PKCS1_OAEP

#cryptography
path = input("Input private key path: ")
pwd = input("Input password: ")
sk = RSA.importKey(open('sk.pem').read(), pwd)
cipher = PKCS1_OAEP.new(sk)

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
    dec = cipher.decrypt(data)
    print('Received',dec)
    if not data: 
        break
    msg = 'ACK'
    conn.sendall(msg.encode())
    conn.close()
