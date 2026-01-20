//
//  ECTextDocument.cpp
//  
//
//

#include "ECTextDocument.h"
#include <iostream>
#include <cctype>

using namespace std;

// **********************************************************
// Commands

// your code goes here 
ECCommandCap :: ECCommandCap(ECTextDocument &docIn, int pos, int lenToCap) : doc(docIn), pos(pos), lenToCap(lenToCap)
{
}

ECCommandCap :: ~ECCommandCap()
{
}

void ECCommandCap :: Execute(){
  int currChar = 0;
  while(currChar<lenToCap){
    doc.CapCharAt(pos+currChar);
    currChar++;
  }
}

void ECCommandCap :: UnExecute()
{
}

ECCommandLow :: ECCommandLow(ECTextDocument &docIn, int posInIns, int lenToLow) : doc(docIn), pos(posInIns), lenToLower(lenToLower)
{
}

ECCommandLow :: ~ECCommandLow()
{
}

void ECCommandLow :: Execute(){
  int currChar = 0;
  while(currChar<lenToLower){
    doc.LowerCharAt(pos+currChar);
    currChar++;
  }
}

void ECCommandLow :: UnExecute()
{
}

ECCommandInsert :: ECCommandInsert(ECTextDocument &docIn, int pos, const std::vector<char> &listCharsToIns): doc(docIn), pos(pos), listChars(listCharsToIns)
{
}

ECCommandInsert :: ~ECCommandInsert()
{
}

void ECCommandInsert :: Execute(){
  vector<char> chars;
  for(int c=listChars.size()-1; c>=0; c--){
    chars.push_back(listChars[c]);
  }

  for(int i=0; i<chars.size(); i++){
    doc.InsertCharAt(pos, chars[i]);
  }
}

void ECCommandInsert :: UnExecute()
{
}

ECCommandRemove :: ECCommandRemove(ECTextDocument &docIn, int pos, int lenToRemove):doc(docIn), pos(pos), lenToRemove(lenToRemove)
{
}

ECCommandRemove :: ~ECCommandRemove() 
{
}

void ECCommandRemove :: Execute(){
  if(pos>doc.GetDocLen()){
    return;
  }

  for(int i=0; i<lenToRemove; i++){
    doc.RemoveCharAt(pos);
  }
  
}

void ECCommandRemove :: UnExecute(){
  return;
}

// **********************************************************
// Controller for text document

ECTextDocumentCtrl :: ECTextDocumentCtrl(ECTextDocument &docIn): document(docIn)
{
  history = new ECCommandHistory();
}

ECTextDocumentCtrl :: ~ECTextDocumentCtrl()
{
}

void ECTextDocumentCtrl :: InsertTextAt(int pos, const std::vector<char> &listCharsToIns)
{
  // your code
  ECCommandInsert *pCmdInsert = new ECCommandInsert(this->document, pos, listCharsToIns);
  history->ExecuteCmd(pCmdInsert);
}

void ECTextDocumentCtrl :: RemoveTextAt(int pos, int lenToRemove)
{
  // your code
  ECCommandRemove *pCmdRemove = new ECCommandRemove(this->document, pos, lenToRemove);
  history->ExecuteCmd(pCmdRemove);
}

void ECTextDocumentCtrl :: CapTextAt(int pos, int lenToCap)
{
  // your code
  ECCommandCap *pCmdCap= new ECCommandCap(this->document, pos, lenToCap);
  history->ExecuteCmd(pCmdCap);
}

void ECTextDocumentCtrl :: LowerTextAt(int pos, int lenToLower)
{
  // your code
  ECCommandLow *pCmdLow = new ECCommandLow(this->document, pos, lenToLower);
  history->ExecuteCmd(pCmdLow);
}

bool ECTextDocumentCtrl :: Undo()
{
  // your code
  return history->Undo();
}

bool ECTextDocumentCtrl :: Redo()
{
  // your code
  return history->Redo();
}

int ECTextDocumentCtrl :: Search(const std::vector<char> &pattern) const
{
  // stub implementation: students should implement search logic
  // expected behavior: return first index of match or -1 if not found
  return -1;
}

void ECTextDocumentCtrl :: ReplaceAt(int pos, int lenToReplace, const std::vector<char> &listCharsToIns)
{
  // stub implementation: students should implement replace logic
}

// **********************************************************
// Document for text document


ECTextDocument :: ECTextDocument() 
{
  docCtrl = new ECTextDocumentCtrl(*this);
}

ECTextDocument :: ~ECTextDocument()
{
}

ECTextDocumentCtrl & ECTextDocument :: GetCtrl()
{
    return *docCtrl;
}

char ECTextDocument :: GetCharAt(int pos) const
{
    return listChars[pos];
}

void ECTextDocument :: InsertCharAt(int pos, char ch)
{
  // your code here
  listChars.insert(listChars.begin()+pos, ch);
}

void ECTextDocument :: RemoveCharAt(int pos)
{
  // your code here
  listChars.erase(listChars.begin()+pos);
}

void ECTextDocument :: CapCharAt(int pos)
{
  // your code here
  listChars[pos] = toupper(listChars[pos]);
}

void ECTextDocument :: LowerCharAt(int pos)
{
  // your code here
  listChars[pos] = tolower(listChars[pos]);
}
