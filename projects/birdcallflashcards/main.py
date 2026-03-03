from playsound3 import playsound
import os
import random
import re

sounds = []

def printOptions(rightAns, numOptions=4):
    '''Populate n random-ordered options with (at least) one correct answer.'''
    options = [rightAns.strip(" 0123456789_+-")]
    rightAnsI = []
    for i in range(0,numOptions-1):
        options.append(sounds[random.randint(0,len(sounds)-1)][:-4].strip(" 0123456789_+-"))

    for i in range(0,numOptions):
        x = random.randint(0,len(options)-1)
        print(f"{i+1}: {options[x]}")
        if(options[x] == rightAns): rightAnsI.append(f"{i+1}")
        options.remove(options[x])
    
    return rightAnsI

def getAcceptedAnswers(stringIn):
    '''Split string in order to output array of accepted parameters: an acronym, split by spaces, and the original file name'''
    stringIn = stringIn.strip(" 0123456789_+-")
    ans = re.split(r"[ _+\-]+", stringIn)
    accAns = []

    nym = ''
    for x in ans:
        if(x=='call' or x=='song'):
            accAns.append(nym)
        nym += x[0]
    
    accAns.append(nym)
    accAns.append(' '.join(ans))
    return accAns

if __name__ == "__main__":
    #get all mp3s in current dir
    with os.scandir('.') as d:
        for f in d:
            if (f.name[-4:] == '.mp3'):
                sounds.append(f.name)

    print("Welcome to Alli's birdcall flashcards!")
    numOptions = input("Enter the number of options per question: ")
    try: numOptions = int(numOptions)
    except: numOptions = 4
    tryAgain = False
    i = random.randint(0,len(sounds)-1)
    while 1:
        if(tryAgain==False): i = random.randint(0,len(sounds)-1)
        call = playsound(sounds[i], False)
        
        #Populate answers and format correct answer
        if(numOptions != 0): corr = printOptions(sounds[i][:-4], numOptions)
        else: corr = []
        corrAns = getAcceptedAnswers(sounds[i][:-4].lower())
        ans = input("Input your answer: ")
        if(ans.lower() == 'exit'): break
        splitAns = re.split(r"[ _+\-]+", ans.lower())
        
        #Do not select a different birdcall if incorrect
        try: call.stop()
        except: print("No call to stop..")
        if(' '.join(splitAns) in corrAns or ans in corr):
            print("<-- Correct! -->")
            tryAgain = False
        elif (ans == 'skip'):
            print("<-- Skipped... -->")
            tryAgain = False
        else:
            print("<-- Try again! -->")
            tryAgain = True
        print('')
