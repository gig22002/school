#!/usr/bin/python3
from socket import *
import _thread as thread

#setup socket connection, same info as server
name = 'localhost'
port = 25565

def conn(_msg):
    sock = socket(AF_INET,SOCK_STREAM)#initialize socket locally
    try:
        sock.connect((name, port)) #connect to socket
        sock.sendall(_msg.encode()) #send bytes

        recvd = sock.recv(1024).decode() #receive bytes
    except Exception as e:
        recvd = str(e)+",400: Bad Request" #handle client app errors

    sock.close() #close connection

    #handle app layer
    print(recvd)
    output=recvd.split(',') #split into output + status code
    if ('20' in output[-1]):
        print(output[:-2],"at",output[-2]) #return all but status
    else:
        print(output[-1],"at",output[-2]) #return status if not successful

while 1:
    print("Please input a query. \'?\' functions as a wildcard.")
    msg = input("Query: ") #get query
    if(msg.lower()=='quit'): 
        break
    
    thread.start_new_thread(conn, (msg, ))