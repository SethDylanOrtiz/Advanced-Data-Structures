#include "Node.h"

Node::Node() : left(nullptr), right(nullptr), pos(0)
{
} // end defaut ctor

Node::Node(const ItemType & anItem) : item(anItem), left(nullptr), right(nullptr), pos(1)
{
} // end ctor

void Node::setItem(const ItemType & anItem)
{
	item = anItem;
} // end setItem

void Node::setLeft(Node* nextLeftPtr)
{
	left = nextLeftPtr;
} // end setLeft

void Node::setRight(Node* nextRightPtr)
{
	right = nextRightPtr;
} // end setRight

Node* Node::getLeft() const
{
	return left;
} // return getLeft

Node* Node::getRight() const
{
	return right;
} // return getRight

ItemType Node::getItem() const
{
	return item;
} // return getItem

int Node::getPos() const
{
	return pos;
} // end getPos

void Node::setPos(const int newPos) 
{
	pos = newPos;
} // end setPos

bool Node::isEmpty() const
{
	return (left == nullptr && right == nullptr);
} // end isEmpty
