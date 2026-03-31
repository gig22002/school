#!/usr/bin/python3
from socket import *

#setup socket connection, same info as server
name = 'localhost'
port = 25565
sock = socket(AF_INET,SOCK_STREAM)

sock.connect((name, port))
msg = input("Query word (\'?\' as wildcard): ")
sock.sendall(msg.encode())

recvd = sock.recv(1024)
print("Obtained", recvd)
sock.close()
