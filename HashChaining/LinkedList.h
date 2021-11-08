#pragma once
#ifndef LINKED_LIST_
#define LINKED_LIST_
#include "Node.h"
#include <string>
#include <iostream>

using namespace std;

typedef pair<string, unsigned> ENTRY;
typedef ENTRY ItemType;
const unsigned MAXENTRIES = 257;

class LinkedList
{
private:
	Node* headPtr; // Pointer to first node in the chain
	Node* tailPtr;  // Pointer to last node
	unsigned itemCount;

	Node* getNodeAt(int position) const; // Locates a specified node in this linked list.
public:
	LinkedList();
	// Copy constructor and destructor are supplied by compiler
	int getLength() const;
	bool insert(const ItemType& newEntry);
	void showList() const;
	unsigned findNode(string const& key) const;
	virtual ~LinkedList();
}; // end ArrayList
#endif
