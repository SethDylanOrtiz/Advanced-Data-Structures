#include "Heap.h"
#include "Node.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

Heap::Heap() : itemCount(0), root(nullptr) // , left(nullptr), right(nullptr)
{
} // end default ctor

bool Heap::isEmpty() const
{
	return itemCount;
} // end isEmpty

int Heap::getSize() const
{
	return itemCount;
} // end getSize

Node* Heap::getRoot() const // for printTree, FIX LATER
{
	return root;
} // end getRoot

void Heap::insert(const ItemType & newEntry)
{
	itemCount++;
	// Check for first insert instance
	if (itemCount == 1)
	{
		root = new Node(newEntry); return;
	}
	Node* parentNode;
	Node* newNodePtr = new Node(newEntry);
	newNodePtr->setPos(itemCount);

	int parent = itemCount / 2;			  // obtain parentNode's position
	parentNode = getNodeAt(parent);

	// find empty child
	parentNode->getLeft() == nullptr ? parentNode->setLeft(newNodePtr) : parentNode->setRight(newNodePtr);

	while(newEntry <= parentNode->getItem())
	{

		// to obtain efficient structure, just swap values within nodes
		newNodePtr->setItem(parentNode->getItem());
		parentNode->setItem(newEntry);
		newNodePtr = parentNode;

		parent /= 2;

		if (parent == 0) return;

		parentNode = getNodeAt(parent);
	} 
} // end insert

void Heap::remove(int position)
{
	Node* lastNode = getNodeAt(itemCount);
	replace(position, lastNode->getItem());

	// get parent, decide which child  to delete based on % position
	itemCount % 2 == 0 ? this->getNodeAt(itemCount / 2)->setLeft(nullptr) : this->getNodeAt(itemCount / 2)->setRight(nullptr);
	delete lastNode;
	itemCount--;
} // end remove

void Heap::replace(const int position, const ItemType & newEntry)
{
	assert(position >= 1 && position <= itemCount);
	// set entryPtr's item to newEntry
	Node* entryPtr = getNodeAt(position);
	entryPtr->setItem(newEntry);

	// if it's smaller than its parent, swap UP
	// otherwise, if its bigger than one of its children, swap DOWN
	unsigned parentPos = position;
	unsigned childPos = position;

	if (position / 2 >= 1)	parentPos = position / 2;

	if (position * 2 <= itemCount) childPos = position * 2;

	while (parentPos >= 1 || childPos <= itemCount)
	{
		Node* parentNode = getNodeAt(parentPos);
		Node* childNode = getNodeAt(childPos);
		if (newEntry < parentNode->getItem()) // swap / swim up
		{
			entryPtr->setItem(parentNode->getItem());
			parentNode->setItem(newEntry);

			entryPtr = parentNode;

			if (parentPos / 2 >= 1) parentPos /= 2;
		}
		else if (newEntry > childNode->getItem()) //  swap / sink down
		{
			entryPtr->setItem(childNode->getItem());
			childNode->setItem(newEntry);

			entryPtr = childNode;

			if (childPos * 2 <= itemCount)	childPos *= 2;
		}
		else
			break;	 // we're in correct position!
	}
} // end replace

Node* Heap::getNodeAt(int position) const
{
	assert(position >= 1 && position <= itemCount);
	vector <unsigned> pathway;

	do
	{
		pathway.insert(pathway.begin(), position);
		position /= 2;
	} while (position > 1);

	Node* curPtr = root;
	for (unsigned step : pathway)
	{
		if (step == curPtr->getPos())
			break;
		if (step == curPtr->getLeft()->getPos())
			curPtr = curPtr->getLeft();
		else
			curPtr = curPtr->getRight();
	}

	return curPtr;
} // end getNodeAt

Heap::~Heap()
{
	while (!isEmpty())
		remove(1);
} // end dtor