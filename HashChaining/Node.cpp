#include "Node.h"

using namespace std;

Node::Node() : next(nullptr)
{
} // end default ctor

Node::Node(const ItemType& anItem) : item(anItem), next(nullptr), prev(nullptr)
{
} // end ctor

Node::Node(const ItemType& anItem, Node* nextNodePtr) : item(anItem), next(nextNodePtr)
{
} // end ctor

void Node::setItem(const ItemType& anItem)
{
	item = anItem;
} // end setItem

void Node::setNext(Node* nextNodePtr)
{
	next = nextNodePtr;
} // end setNext

Node* Node::getNext() const
{
	return next;
} // end getNext

string Node::getKey() const
{
	return item.first;
} // end getKey

unsigned Node::getUnsigned() const
{
	return item.second;
} // end getUnsigned
