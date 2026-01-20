//
//  ECCommand.cpp
//  
//

#include "ECCommand.h"

// ******************************************************
// Implement command history

ECCommandHistory :: ECCommandHistory() 
{
  // your code goes here
  currCommand = -1;
}

ECCommandHistory :: ~ECCommandHistory()
{
  // your code goes here
  for (auto it : commands){
    delete it;
  }
}

bool ECCommandHistory :: Undo(){
  if(currCommand>=0){
    commands[currCommand]->UnExecute();
    currCommand--;
    return 1;
  }
  return 0;
}

bool ECCommandHistory :: Redo(){
  if(currCommand < commands.size()){
    commands[currCommand]->Execute();
    currCommand++;
    return 1;
  }
  return 0;
}

void ECCommandHistory :: ExecuteCmd(ECCommand *pCmd){
  // for(int i=commands.size(); i>currCommand; i++){
  //   delete commands[i];
  //   commands.pop_back();
  // }
  // commands.push_back(pCmd);
  // pCmd->Execute();
  // currCommand++;
  pCmd->Execute();
  commands.push_back(pCmd);
}