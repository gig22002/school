#!/usr/bin/python3
from socket import *

#setup socket connection, same info as server
name = 'localhost'
port = 25565
sock = socket(AF_INET,SOCK_STREAM)

sock.connect((name, port)) #connect to socket
msg = input("Query word (\'?\' as wildcard): ") #get query
sock.sendall(msg.encode()) #send bytes

recvd = sock.recv(1024)
print("Obtained", recvd) #print received output
sock.close()
