from playsound3 import playsound
import os
import random

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
        if(options[x] == rightAns): rightAnsI.append(i+1); print(rightAnsI)
        options.remove(options[x])
    return rightAnsI
    
        

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
        sound = playsound(sounds[i], False)
        corr = printOptions(sounds[i][:-4])
        ans = input("Input your answer: ")
        print(corr)
        if(ans.lower() == sounds[i][:-4].lower() or ans in corr):
            print("Correct!")
            tryAgain = False
        else:
            print("Try again!")
            tryAgain = True
        sound.stop()