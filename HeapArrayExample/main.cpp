// CS 532, Seth Ortiz, Hw5Review - Heaps, 5/17/2019
#include <iostream>

using namespace std;

void heapSort(int arr[], int size);
void heapify(int arr[], int size, int i);
bool checkMinHeap(int arr[], int size, int i);
bool checkMaxHeap(int arr[], int size, int i);
void show(int arr[], int elem);

int main()
{
	// minHeaps
	int notMin[6] = { 12, 11, 13, 5, 6, 7 };
	int isMin[7] = { 12, 2, 10, 0, 1, 7, 8 };

	// maxHeaps
	int isMax[5] = { 70, 55, 40, 35, 10 };
	int notMax[5] = { 70, 55, 40, 35, 80 };

	heapSort(isMin, 7);
	cout << "Min Heapified Array: ";
	show(isMin, 7);
	checkMinHeap(isMin, 7, 0) ? cout << "Array is a MinHeap \n" : cout << "Array is not a MinHeap\n";
	checkMinHeap(notMin, 6, 0) ? cout << "Array is a MinHeap \n" : cout << "Array is not a MinHeap\n";

	checkMaxHeap(isMax, 5, 0) ? cout << "Array is a MaxHeap \n" : cout << "Array is not a MaxHeap\n";
	checkMaxHeap(notMax, 5, 0) ? cout << "Array is a MaxHeap \n" : cout << "Array is not a MaxHeap\n";

	return 0;
}

void heapSort(int arr[], int size)
{
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i); // build heap (rearrange array)

	for (int i = size - 1; i >= 0; i--) // one by one extract element from heap
	{
		swap(arr[0], arr[i]); // move current root to end
		heapify(arr, i, 0); // call maxHeapify on reduced heap
	}
} // end heapSort

void heapify(int arr[], int size, int i)
{
	int largest = i; // largest temp holder
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < size && arr[left] > arr[largest]) // if left child is greater than root
		largest = left;
	if (right < size && arr[right] > arr[largest]) // if right child is greater largest so far
		largest = right;

	if (largest != i) // if largest is not root
	{
		swap(arr[i], arr[largest]);
		heapify(arr, size, largest); // recursively heapify the effected subtree
	}
}

bool checkMinHeap(int arr[], int size, int i)
{
	if (2 * i + 2 > size) // if current node is a leaf, return true as every leaf is a heap
		return true;
	// if internal <= left child 
	bool trueLeft = (arr[i] <= arr[2 * i + 1] && checkMinHeap(arr, size, 2 * i + 1)); // recursively call, pass left node
					// then, check if internal <= right child || were at last node
	bool trueRight(arr[i] <= arr[2 * i + 2] || 2 * i + 2 == size && checkMinHeap(arr, size, 2 * i + 2));

	return trueLeft && trueRight; // return true if both left and right represent minHeap
} // end checkMinHeap

bool checkMaxHeap(int arr[], int size, int i)
{
	if (i > (size - 2) / 2) // if current node is leaf
		return true;
	// if internal node > left child		 recursively pass left child
	bool trueLeft = (arr[i] > arr[2 * i + 1] && checkMaxHeap(arr, size, 2 * i + 1));
	// then, check if internal node > right child || were at last node, recursively pass right child
	bool trueRight = (arr[i] > arr[2 * i + 2] || (2 * i + 2 == size) && checkMaxHeap(arr, size, 2 * i + 2));

	return trueLeft && trueRight; // return true if both left and right represent maxHeap
} // end checkMaxHeap

void show(int arr[], int elem)
{
	for (int i = 0; i < elem; i++)
		cout << arr[i] << " ";
	cout << "\n\n";
} // end show
