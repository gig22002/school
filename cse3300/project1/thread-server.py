#!/usr/bin/python3
"""
Server side: open a socket on a port, listen for a message from a client,
and send an echo reply; echoes lines until eof when client closes socket;
spawns a thread to handle each client connection; threads share global
memory space with main thread; this is more portable than fork: threads
work on standard Windows systems, but process forks do not;
"""

import time, _thread as thread           # or use threading.Thread().start()
from socket import *                     # get socket constructor and constants
from collections import defaultdict

#same file reading and dict creating as server.py
with open("wordlist.txt","r") as f:
    wordarr = f.read().splitlines() #create array of all the words
    words = defaultdict(list)
    for x in wordarr:
        words[x[0]].append(x) #arrange the words in a dict by letter as key

def searchWords(word):
    out = []
    #initialize array to iterate
    if(word[0]!='?'):
        arr = words[word[0]] #speed up query via dicts
    else: arr=wordarr
    skip = False
    for x in arr:
        for i in range(1,len(word)): #for each letter of each word
            if(len(x)<=i): #prevent errors
                skip = True
                break
            if(x[i]!=word[i] and word[i]!='?'): #check letter
                skip = True
                break
            skip = False
        if skip: continue
        if len(x)==len(word): out.append(x) #append IFF bounded

    return out

myHost = ''                              # server machine, '' means local host
myPort = 25565# listen on a non-reserved port number

sockobj = socket(AF_INET, SOCK_STREAM)           # make a TCP socket object
sockobj.bind((myHost, myPort))                   # bind it to server port number
sockobj.listen(5)                                # allow up to 5 pending connects

def now():
    return time.ctime(time.time())               # current time on the server

def handleClient(connection):                    # in spawned thread: reply
    time.sleep(5)                                # simulate a blocking activity
    while True:                                  # read, write a client socket
        data = connection.recv(1024)
        if not data:
            msg = "No data,400: Bad Request"
            break
        try:
            msg = ','.join(searchWords(data.decode())) #search words
            if len(msg)==0: msg = ","+now()+",404: Not Found" #if string is empty
            else: msg+=","+now()+",200: OK" #append successful code
        except Exception as e:
            msg = str(e)+","+now()+",500: Internal Server Error" #if other error
        print("Sending",msg)
        connection.sendall(msg.encode())
    connection.close()

def dispatcher():                                # listen until process killed
    while True:                                  # wait for next connection,
        connection, address = sockobj.accept()   # pass to thread for service
        print('Server connected by', address, end=' ')
        print('at', now())
        thread.start_new_thread(handleClient, (connection,))

dispatcher()
