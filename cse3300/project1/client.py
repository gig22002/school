#!/usr/bin/python3
from socket import *

#setup socket connection, same info as server
name = 'localhost'
port = 25565
sock = socket(AF_INET,SOCK_STREAM)

print("Please input a query. \'?\' functions as a wildcard.")
msg = input("Query: ") #get query
try:
    sock.connect((name, port)) #connect to socket
    sock.sendall(msg.encode()) #send bytes

    recvd = sock.recv(1024)
except Exception as e:
    recvd = str(e)+",400: Bad Request"
print("Obtained", recvd) #print received output

#handle app layer
output=recvd.decode().split(',')
print(output)
sock.close()
