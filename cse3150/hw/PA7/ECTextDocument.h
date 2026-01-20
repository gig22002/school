//
//  ECTextDocument.h
//  
//
//

#ifndef ECTextDocument_h
#define ECTextDocument_h

#include "ECCommand.h"
#include <vector>

class ECTextDocument;

// **********************************************************
// Implements Commands for editing 


// your code goes here
class ECCommandCap : public ECCommand
{
public:
    ECCommandCap(ECTextDocument &docIn, int pos, int lenToCap);
    ~ECCommandCap();
    void Execute();
    void UnExecute();
private:
    ECTextDocument &doc;
    int pos;
    int lenToCap;
};

class ECCommandLow : public ECCommand
{
public:
    ECCommandLow(ECTextDocument &docIn, int posInIns, int lenToLow);
    ~ECCommandLow();
    void Execute();
    void UnExecute();
private:
    ECTextDocument &doc;
    int pos;
    int lenToLower;
};

class ECCommandInsert : public ECCommand
{
public:
    ECCommandInsert(ECTextDocument &docIn, int pos, const std::vector<char> &listCharsToIns);
    ~ECCommandInsert();
    void Execute();
    void UnExecute();
private:
    ECTextDocument &doc;
    int pos;
    const std::vector<char> &listChars;
};

class ECCommandRemove : public ECCommand
{
public:
    ECCommandRemove(ECTextDocument &docIn, int pos, int lenToRemove);
    ~ECCommandRemove();
    void Execute();
    void UnExecute();
private:
    ECTextDocument &doc;
    int pos;
    int lenToRemove;
};


// **********************************************************
// Controller for text document

class ECTextDocumentCtrl
{
public:
    ECTextDocumentCtrl(ECTextDocument &docIn);          // conroller constructor takes the document as input
    virtual ~ECTextDocumentCtrl();
    void InsertTextAt(int pos, const std::vector<char> &listCharsToIns);    // insert a list of characters starting at position
    void RemoveTextAt(int pos, int lenToRemove);                            // remove a segment of characters  of lenToRemove starting from pos
    void CapTextAt(int pos, int lenToCap);                                  // Capitalize the text of lenToCap long starting from pos
    void LowerTextAt(int pos, int lenToLower);                              // Lowercase the text of lenToLoer starting from pos
    int Search(const std::vector<char> &pattern) const;                     // Return first index of matching pattern; -1 if not found
    void ReplaceAt(int pos, int lenToReplace, const std::vector<char> &listCharsToIns); // Replace text at pos with given list
    bool Undo();                                                            // undo any change you did to the text
    bool Redo();                                                            // redo the change to the text
    
private:
    // your code
    ECTextDocument &document;
    ECCommandHistory* history;
};

// **********************************************************
// Document for text document

class ECTextDocument
{
public:
    ECTextDocument();
    virtual ~ECTextDocument();
    ECTextDocumentCtrl &GetCtrl();          // return document controller
    int GetDocLen() const { return listChars.size(); }
    char GetCharAt(int pos) const;          // get char at current position
    void InsertCharAt(int pos, char ch);    // insert a single char at position
    void RemoveCharAt(int pos);             // erase a single char at position
    void CapCharAt(int pos);                // capitalize the char at position
    void LowerCharAt(int pos);              // lowercase the char at position
    
private:
    // your code
    std::vector<char> listChars;
    ECTextDocumentCtrl* docCtrl;
};


#endif /* ECTextDocument_h */
