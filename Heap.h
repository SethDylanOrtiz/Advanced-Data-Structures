#pragma once
#ifndef HEAP_
#define HEAP_
#define COUNT 10

#include "Node.h"
#include <string>
#include <queue>

typedef int ItemType;

class Heap
{
private:
	int	itemCount;
	Node* root;
public:
	Heap();

	bool isEmpty() const;
	int getSize() const;
	Node* getRoot() const;
	Node* getNodeAt(int pos) const;	

	void remove(int position);
	void insert(const ItemType& newEntry);				
	void replace(const int position, const ItemType& newEntry);

	virtual ~Heap();
}; // end Heap
#endif