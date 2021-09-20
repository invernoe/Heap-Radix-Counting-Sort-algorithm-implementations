#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

static int arraySize = 30;
int countComparisons = 0;

void countingSort(int *a, int exp = -1) {

	int k = arraySize;

	int *b = new int[arraySize];
	int *c = new int[k + 1]{};

	if (exp <= 0) {
		for (int i = 0; i < arraySize; i++)
		{
			c[a[i]]++;
			countComparisons++;
		}
	}
	else {
		for (int i = 0; i < arraySize; i++)
		{
			c[(a[i] / exp) % 10]++;
		}
	}

	for (int i = 1; i <= k; i++)
		c[i] += c[i - 1];

	if (exp <= 0) {
		for (int i = arraySize - 1; i >= 0; i--)
		{
			b[c[a[i]] - 1] = a[i];
			c[a[i]]--;
			countComparisons++;
		}
	}
	else {
		for (int i = arraySize - 1; i >= 0; i--)
		{
			b[c[(a[i] / exp) % 10] - 1] = a[i];
			c[(a[i] / exp) % 10]--;
		}
	}

	for (int i = 0; i < arraySize; i++)
	{
		a[i] = b[i];
	}

	delete[] b;
	delete[] c;
}

void maxHeapify(int *a, int i, int heapSize) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < heapSize && a[left] > a[largest])
		largest = left;

	if (right < heapSize && a[right] > a[largest])
		largest = right;

	if (largest != i)
	{
		int tmp = a[i];
		a[i] = a[largest];
		a[largest] = tmp;
		maxHeapify(a, largest, heapSize);
	}

	countComparisons++;

}

void buildMaxHeap(int *a) {

	for (int i = (arraySize / 2) - 1; i >= 0; i--)
		maxHeapify(a, i, arraySize);

}

void heapSort(int *a) {

	buildMaxHeap(a);

	for (int i = arraySize - 1; i > 0; i--)
	{
		int tmp = a[i];
		a[i] = a[0];
		a[0] = tmp;
		maxHeapify(a, 0, i);
	}
}

int getMax(int *a)
{
	int max = a[0];
	for (int i = 1; i < arraySize; i++)
		if (a[i] > max)
			max = a[i];
	return max;
}

void radixsort(int *a)
{
	int max = getMax(a);

	for (int exp = 1; max / exp > 0; exp *= 10)
		countingSort(a, exp);
}

int* generateData(int size, int type) {

	int *p = new int[size];

	switch (type)
	{
	case 0:
		for (int i = 0; i < size; i++)
		{
			p[i] = rand() % (size + 1);
		}
		break;

	case 1:
		for (int i = 0; i < size; i++)
		{
			p[i] = i;
		}
		break;

	case 2:
		for (int i = 0; i < size; i++)
		{
			p[i] = size - i - 1;
		}
		break;

	default:
		break;
	}

	return p;
}

void main() {

	int *a = generateData(arraySize, 0);
	for (int i = 0; i < arraySize; i++)
	{
		cout << a[i] << "\t";
	}
	cout << "\n\n";

	int sort = 0; //variable that lets us pick the sorting algorithm, can take a value of either 0, 1, or 2
	switch (sort) {
	case 0:
		heapSort(a);
		break;
	case 1:
		countingSort(a);
		break;
	case 2:
		radixsort(a);
		break;
	default:
		cout << "error\n";
		break;
	}

	for (int i = 0; i < arraySize; i++)
	{
		cout << a[i] << "\t";
	}
	cout << "\ncount = " << countComparisons << "\n";

	delete[] a;

	system("pause");
}