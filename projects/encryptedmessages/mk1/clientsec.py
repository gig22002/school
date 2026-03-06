from socket import *
from Cryptodome.PublicKey import RSA
from Cryptodome.Cipher import PKCS1_OAEP

def genkey(passwd='test'):
    key = RSA.generate(2048)
    pwd = passwd.encode()
    with open("sk_client.pem", "wb") as f:
        data = key.export_key(passphrase=pwd,
                              pkcs=8,
                              protection='PBKDF2WithHMAC-SHA512AndAES256-CBC',
                              prot_params={'iteration_count':131072})
        f.write(data)

    with open("sk_client.pem", "rb") as f:
        data = f.read()
        key = RSA.import_key(data, pwd)

    with open("pk_client.pem", "wb") as f:
        data = key.public_key().export_key()
        f.write(data)

try:
    pk = RSA.import_key(open('pk_client.pem').read())
except:
    genkey()
    pk = RSA.import_key(open('pk_client.pem').read())
cipher = PKCS1_OAEP.new(pk)

host = 'localhost'
port = 25565

while 1:
    s = socket(AF_INET, SOCK_STREAM)
    s.setsockopt(SOL_SOCKET, SO_KEEPALIVE, 1)
    s.connect((host, port))

    msg = input("Enter message: ")
    if not msg:
        break
    s.sendall(cipher.encrypt(msg.encode()))

    data = s.recv(1024)
    print('Received',data,'from server')
    s.close()
