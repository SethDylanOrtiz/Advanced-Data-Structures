#pragma once
#ifndef NODE_
#define NODE_
#include <string>

using namespace std;

typedef pair<string, unsigned> ENTRY;
typedef ENTRY ItemType;

class Node
{
private:
	ItemType  item;  // A data item
	Node* next;  // Pointer to next node
	Node* prev;  // Pointer to previous node

public:
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node* nextNodePtr);
	void setItem(const ItemType& anItem);
	void setNext(Node* nextNodePtr);
	Node* getNext() const;

	unsigned getUnsigned() const;
	string getKey() const;

}; // end Node
#endif
