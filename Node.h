#pragma once
#ifndef NODE_
#define NODE_
#include <string>

using namespace std;
typedef int ItemType;

class Node
{
private:
	ItemType  item;  // A data item
	Node*	  root;
	Node*	  left;
	Node*	  right;
	int		  pos;

public:
	Node();
	Node(const ItemType& anItem);
	ItemType getItem() const;
	void setItem(const ItemType& anItem);
	Node* getLeft() const;
	void setLeft(Node* nextLeftPtr);
	Node* getRight() const;
	void setRight(Node* nextRightPtr);

	bool isEmpty() const;
	int getPos() const;
	void setPos(int newPos);
}; // end Node
#endif