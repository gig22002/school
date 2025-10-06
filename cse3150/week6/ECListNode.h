#ifndef _EC_LIST_NODE_H
#define _EC_LIST_NODE_H

#include <iostream>

// Class for linked list node
class ECListNode
{
public:
  ECListNode() {}
  ECListNode(int v) : data(v), next(nullptr){}
  ECListNode *GetNext() const { return next; }
  void SetNext(ECListNode *pn) { next = pn; }
  int GetValue() const { return data; }
  void SetValue(int v) { data = v; }

private:
  // ???
  int data;
  ECListNode *next;
};

#endif
