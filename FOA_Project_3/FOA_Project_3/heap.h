#ifndef heap_h
#define heap_h

#include <vector>

template<typename T>
class heapSortAlgo
{
private:
	std::vector<T> list;
public:

	heapSortAlgo();
	int parent(int i)
	{
		return (i + 1) / 2 - 1;
	}

	int left(int i)
	{
		return 2 * i + 1;
	}
	int right(int i)
	{
		return 2 * i + 2;
	}

	int getItem(int n)
	{

	}
	void initializeMaxHeap(std::vector<T> wordList);
	void buildMaxHeap(int heapSize);
	void maxHeapify(int i, int heapSize);
	void initializeMinHeap(std::vector<T> wordList);
	void buildMinHeapify(int heapSize);
	void minHeapify(int i, int heapSize);
	void heapSort();

	// return the word giving the index
	std::vector<T> getSortedWordList();

	//T getItem(int i);
};
/*
* Empty constructor
*/
template<typename T>
heapSortAlgo<T>::heapSortAlgo()
{
}

/*
*Initialize the MaxHeap by storing getting the wordList.
*
*/
template<typename T>
void heapSortAlgo<T>::initializeMaxHeap(std::vector<T> wordList)
{
	for (int i = 0; i < (int)wordList.size(); i++)
	{
		list.push_back(wordList[i]);
	}
}

template<typename T>
void heapSortAlgo<T>::buildMaxHeap(int heapSize)
{
	for (int i = (heapSize + 1) / 2; i >= 0; i--)
	{
		maxHeapify(i, heapSize);
	}

}
/*
* Sort the vector using maxHeapify
*/
template<typename T>
void heapSortAlgo<T>::maxHeapify(int i, int heapSize)
{
	int largest;
	T temp;
	int l = left(i);
	int r = right(i);
	if (l <= heapSize - 1 && list[l] > list[i])
		largest = l;
	else
		largest = i;

	if (r <= heapSize - 1 && list[r] > list[largest])
		largest = r;
	if (largest != i)
	{
		temp = list[largest];
		list[largest] = list[i];
		list[i] = temp;
		maxHeapify(largest, heapSize);
	}
}

/*
* Initialize the vector
*/
template<typename T>
void heapSortAlgo<T>::initializeMinHeap(std::vector<T> wordList)
{
	for (int i = 0; i < wordList.size(); i++)
	{
		list.push_back(wordList[i]);
	}
}


template<typename T>
void heapSortAlgo<T>::buildMinHeapify(int heapSize)
{
	for (int i = (heapSize + 1) / 2; i >= 0; i--)
	{
		minHeapify(i, heapSize);
	}
}
/*
*sort list using minHeapify
*/
template<typename T>
void heapSortAlgo<T>::minHeapify(int i, int heapSize)
{
	int smallest;
	T temp;
	int l = left(i);
	int r = right(i);
	if (l <= heapSize - 1 && list[l] < list[i])
		smallest = l;
	else
		smallest = i;

	if (r <= heapSize - 1 && list[r] < list[smallest])
		smallest = r;
	if (smallest != i)
	{
		temp = list[smallest];
		list[smallest] = list[i];
		list[i] = temp;
		maxHeapify(smallest, heapSize);
	}
}

/*
*return the sorted list
*/
template<typename T>
std::vector<T> heapSortAlgo<T>::getSortedWordList()
{
	return list;
}

/*
*Heapsort using Max-heapify
*/
template<typename T>
void heapSortAlgo<T>::heapSort()
{
	T temp;	//declare a temp variable to store word
	int heapSize = list.size();

	buildMaxHeap(heapSize);

	for (int j = list.size() - 1; j >= 1; j--)
	{
		temp = list[j];
		list[j] = list[0];
		list[0] = temp;
		heapSize--;
		maxHeapify(0, heapSize);
	}
}
#endif // !heap_h

