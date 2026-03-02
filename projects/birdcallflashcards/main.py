from playsound3 import playsound
import os
import random
import re

sounds = []

def printOptions(rightAns):
    options = [rightAns]
    rightAnsI = []
    options.append(sounds[random.randint(0,len(sounds)-1)][:-4])
    options.append(sounds[random.randint(0,len(sounds)-1)][:-4])
    options.append(sounds[random.randint(0,len(sounds)-1)][:-4])

    for i in range(0,4):
        x = random.randint(0,len(options)-1)
        print(f"{i+1}: {options[x]}")
        if(options[x] == rightAns): rightAnsI.append(f"{i+1}")
        options.remove(options[x])
    
    return rightAnsI

def getAcceptedAnswers(stringIn):
    ans = re.split(r"[ _+\-]+", stringIn)
    nym = ''
    for x in ans:
        nym += x[0]
    
    accAns = [nym]
    accAns.append(' '.join(ans))
    accAns.append(stringIn)
    return accAns

if __name__ == "__main__":
    #get all mp3s in current dir
    with os.scandir('.') as d:
        for f in d:
            if (f.name[-4:] == '.mp3'):
                sounds.append(f.name)

    tryAgain = False
    i = random.randint(0,len(sounds)-1)
    while 1:
        if(tryAgain): i = random.randint(0,len(sounds)-1)
        call = playsound(sounds[i], False)
        corr = printOptions(sounds[i][:-4])
        corrAns = getAcceptedAnswers(sounds[i][:-4].lower())
        ans = input("Input your answer: ")
        if(ans.lower() in corrAns or ans in corr):
            print("Correct!")
            tryAgain = False
        else:
            print("Try again!")
            tryAgain = True
        call.stop()
