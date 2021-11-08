#include "LinkedList.h"
#include <cassert>

using namespace std;

LinkedList::LinkedList() : headPtr(nullptr), itemCount(0), tailPtr(nullptr)
{
}  // end default constructor

int LinkedList::getLength() const
{
	return itemCount;
}  // end getLength

bool LinkedList::insert(const ItemType& newEntry)
{
	itemCount++;
	Node* newNodePtr = new Node(newEntry);
	if (itemCount == 1)
	{
		newNodePtr->setNext(headPtr); // Insert new node at beginning of chain
		headPtr = newNodePtr;
	}
	else
	{
		Node* prevPtr = getNodeAt(itemCount - 1); // Find node that will be before new node

		// Insert new node after node to which prevPtr points
		newNodePtr->setNext(prevPtr->getNext()); // or null ptr
		prevPtr->setNext(newNodePtr);
	}
	return true;
} // end insert

unsigned LinkedList::findNode(string const& key) const
{
	Node* curPtr = headPtr;
	while (curPtr != nullptr)
	{
		if (curPtr->getKey() == key)
			return curPtr->getUnsigned();
		curPtr = curPtr->getNext();
	}
	return UINT_MAX; // if not found
} // end findNode

Node* LinkedList::getNodeAt(int position) const
{
	assert((position >= 1) && (position <= itemCount)); // Debugging check of precondition

	// Count from the beginning of the chain til pos
	Node* curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr; // return pos node
}  // end getNodeAt

void LinkedList::showList() const
{
	Node* curPtr = headPtr;
	for (unsigned i = 0; i < itemCount; i++)
	{
		cout << curPtr->getKey() << ", " << curPtr->getUnsigned() << " ";
		curPtr = curPtr->getNext();
		if (curPtr != nullptr)
			cout << "----> ";
	}
} // showList

LinkedList::~LinkedList()
{
	delete headPtr;
	delete tailPtr;
} // end destructor
