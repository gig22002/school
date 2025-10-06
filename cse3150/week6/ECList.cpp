#include "ECListNode.h"
#include "ECList.h"

// Linked list 
ECList :: ECList() 
{
	pHead = nullptr;
	numNodes = 0;
}
  
// insert node with value val after a node
// if node is NULL, insert to the front
void ECList :: Insert(int val, ECListNode *pPre)
{
	ECListNode *newNode = new ECListNode(val);
	if(pPre != nullptr){
		newNode->SetNext(pPre->GetNext());
		pPre->SetNext(newNode);
	} else {
		newNode->SetNext(pHead);
		pHead = newNode;
	}
	numNodes++;
}

// delete a node
void ECList :: Delete(ECListNode *pNode)
{
	if(pNode == pHead) { pHead = pHead->GetNext(); } 
	else {
		ECListNode *prev = pHead;
		while(prev->GetNext() != pNode){
			prev = prev->GetNext();
		}
		prev->SetNext(pNode->GetNext());
	}

	delete pNode;
	numNodes--;
}

// get a node with value; if multiple nodes with the same value, return the first from head
ECListNode * ECList::GetNode(int val)
{
	ECListNode *curr = pHead;
	while(curr != nullptr){
		if(curr->GetValue() == val)
			return curr;
		curr = curr->GetNext();
	}
	return nullptr;
}

// get the number of nodes in the list
int ECList:: GetSize() const
{
	return numNodes;
}

