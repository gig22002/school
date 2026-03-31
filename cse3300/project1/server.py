#!/usr/bin/python3
from collections import defaultdict
from socket import *

with open("wordlist.txt","r") as f:
    wordarr = f.read().splitlines()
    words = defaultdict(list)
    for x in wordarr:
        words[x[0]].append(x) #arrange the words in a dict by letter as key

def searchWords(word):
    out = []
    #initialize array to iterate
    if(word[0]!='?'):
        arr = words[word[0]]
    else: arr=wordarr
    for x in arr:
        for i in range(1,len(word)): #for each letter of each word
            if(len(x)<=i): #prevent errors
                skip = True
                break
            if(x[i]!=word[i] and word[i]!='?'): #check letter
                skip = True
                break
            skip = False
        if skip:
            continue
        if len(x)==len(word): out.append(x) #append IFF bounded

    return out

#print(searchWords('an?'))

host = "localhost"
port = 25565 #arbitrary non-privileged port
sock = socket(AF_INET,SOCK_STREAM)
sock.bind((host,port))

sock.listen(1) #backlog of 1 unaccepted conn

while 1:
    conn, addr = sock.accept() #accept a connection
    print("Connected to", addr)

    _in = conn.recv(1024) #receive client input
    print("Received:", _in)
    conn.sendall("200: OK") #send successful response
    conn.close()

