// CS 532, Seth Ortiz, HeapNodeExample, 5/20/2019
#include "Node.h"
#include "Heap.h"
#include <iostream>

using namespace std;
void printTree(Node* root, unsigned space);

int main()
{
	Heap myheap;

	for (int i = 5; i <= 90; i += 5)
		myheap.insert(i);
	printTree(myheap.getRoot(), 0);

	cout << "Removing position 6 \n\n";
	myheap.remove(6);
	printTree(myheap.getRoot(), 0);
	cout << "itemCount: " << myheap.getSize() << "\n\n";

	cout << "Inserting value 2 \n\n";
	myheap.insert(2);
	printTree(myheap.getRoot(), 0);
	cout << "itemCount: " << myheap.getSize() << "\n\n";

	cout << "Replacing  position 1 with value 81 \n\n";
	myheap.replace(1,81);
	printTree(myheap.getRoot(), 0);
	cout << "itemCount: " << myheap.getSize() << "\n\n";

	cout << "Replacing position 14 with value 6 \n\n";
	myheap.replace(14, 6);
	printTree(myheap.getRoot(), 0);
	cout << "itemCount: " << myheap.getSize() << "\n\n";

	return 0;
}

// algorithm : https://www.geeksforgeeks.org/print-binary-tree-2-dimensions/
void printTree(Node* root, unsigned space)
{
	if (root == nullptr) return;

	space += COUNT;

	printTree(root->getRight(), space);

	cout << endl;
	for (unsigned i = COUNT; i < space; i++)
		cout << " ";
	cout << root->getItem() << '\n';

	printTree(root->getLeft(), space);
} // end printTree