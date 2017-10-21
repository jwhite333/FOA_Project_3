#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "d_except.h"
#include "helpers.h"
#include "hash.h"
#include "heap.h"

using namespace std;

class wordList
{
private:
	// Private member variables
	vector<string> list;
	vector<string> availableListFiles = { "wordlist.txt", "wordlist2.txt" };

	/*
	 * pickListFile
	 *
	 * Chooses one of the list files to open
	 */
	string pickListFile()
	{
		enum inputError
		{
			NONE,
			NOT_A_NUM,
			OUT_OF_RANGE
		};

		// Get user input
		int input;
		inputError error;
		do
		{
			try
			{
				// Ask user to pick a file
				cout << "Choose a word list file to open:" << endl << endl;
				for (int i = 0; i < (int) availableListFiles.size(); i++)
				{
					cout << i + 1 << " - " << availableListFiles[i] << endl;
				}
				cout << "Enter numerical choice: ";
				cin >> input;

				// Catch bad input
				if (cin.fail())
					throw inputError::NOT_A_NUM;

				// Catch out of range input
				if (input <= 0 || input > (int) availableListFiles.size())
					throw inputError::OUT_OF_RANGE;

				error = inputError::NONE;
			}
			catch (inputError e)
			{
				// Set error flag
				error = e;

				// Display error for bad input
				if (e == inputError::NOT_A_NUM)
					cout << "ERROR, input not a number" << endl;
				if (e == inputError::OUT_OF_RANGE)
					cout << "ERROR, input is not one of the available options" << endl;

				// Clear cin buffer
				cin.clear();
				cin.ignore(cin.rdbuf()->in_avail(), '\n');
			}

		} while (error != inputError::NONE);

		// Choose list file
		return availableListFiles[input - 1];
	}

public:
	// Public member variables
	hashTable * table;
	int maxWordLength;

	/*
	 * constructor
	 *
	 * Initializes hash table to be a null pointer
	 */
	wordList(SORTING_ALGORITHM algorithm)
	{
		// Initialize hash table flag / ptr
		if (algorithm == HASH_TABLE)
			table = new hashTable(9007);
		else
			table = NULL;

		maxWordLength = 0;
	}

	/*
	 * destructor
	 *
	 * Deletes the hash table if it exists
	 */
	~wordList()
	{
		if (table)
			delete table;
	}

	/*
	 * readlist
	 *
	 * Reads words from the specified text file and returns them in a vector of strings
	 */
	void readlist()
	{
		// Open file
		string file = pickListFile();
		ifstream inFile;
		inFile.open(file.c_str());
		if (inFile.bad())
			throw fileOpenError(file);

		// Initialize vector, overwriting old vector if necessary
		if ((int)list.size() > 0)
			list.resize(0);

		// Read file
		string word;
		while (getline(inFile, word))
		{
			if (inFile.bad())
				throw fileError("getline failed");

			// Add element to list or hash table, depending on algorithm selected
			if (table)
				table->addItem(word);
			else
				list.push_back(word);

			// Store the size of the largest word in the dictionary
			maxWordLength = max(maxWordLength, (int)word.length());
		}
	}

	/*
	 * print
	 *
	 * Prints the current word list to sdout
	 */
	void print()
	{
		// Print
		cout << "Word list contains:" << endl;
		for (int i = 0; i < (int)list.size(); i++)
		{
			cout << list[i] << endl;
		}
	}

	/*
	 * print
	 *
	 * Prints the specified word to stdout
	 */
	void print(int index)
	{
		if (index >= 0 && index < (int) list.size())
			cout << list[index] << endl;
	}

	/*
	 * find
	 *
	 * Returns the index of the word if it resides in the word list (binary search)
	 * Returns -1 on failure
	 */
	findResult find(string word)
	{
		int sublistBegin = 0;
		int subListEnd = list.size() - 1;

		// Look for the word using a binary search
		int guess = (sublistBegin + subListEnd) / 2;
		while (guess != sublistBegin && guess != subListEnd)
		{
			// Word was found
			if (list[guess] == word)
				return findResult({ guess }, FOUND);

			// Change the size of the sublist based on where the guess was in relation to the word
			if (list[guess].compare(word) < 0)
				sublistBegin = guess;
			else
				subListEnd = guess;
			
			// Guess again
			guess = (sublistBegin + subListEnd) / 2;
		}

		// Word was not found, check if it is a substring. Might be off by +/- 1 though so check all 3 cases
		for (int offset = -1; offset < 2; offset++)
		{
			// Check if offsets are in the list
			if (guess + offset >= 0 && guess + offset < (int)list.size())
			{
				// Check if the offset word is long enough to need to compare
				if ((int)list[guess + offset].length() >= (int)word.length())
				{
					// Check for a match with the first word.length() characters in the word
					bool match = true;
					for (int index = 0; index < (int)word.length(); index++)
					{
						if (word[index] != list[guess + offset][index])
							match = false;
					}
					if (match)
					{
						// Result is a substring of at least one word in the list
						return findResult({ guess }, SUBSTRING);
					}
				}
			}
		}

		// Result is not a substring of anything in the list
		return findResult({}, NOT_FOUND);
	}

	/*
	 * sort
	 *
	 * Sorts the words using one of the 3 sorting algorithms
	 */
	void sort(SORTING_ALGORITHM algorithm)
	{
		switch (algorithm)
		{
		case INSERTION_SORT:
			insertionSort();
			break;

		case QUICK_SORT:
			quickSort();
			break;

		case MERGE_SORT:
			mergeSort();
			break;

		case HASH_TABLE:
			return;
			break;

		case HEAP_SORT:
			heapSort();
			break;
		}
	}

	/*
	 * insertionSort
	 *
	 * Sorts word list using insertion sort
	 */
	void insertionSort()
	{
		string word;
		int i;
		for (int j = 1; j < (int) list.size(); j++)
		{
			word = list[j];
			i = j - 1;
			while (i >= 0 && list[i] > word)
			{
				list[i + 1] = list[i];
				i = i - 1;
			}
			list[i + 1] = word;
		}
	}

	/*
	 * quickSort
	 *
	 * Sorts word list using quick sort
	 */
	void quickSort()
	{
		quickSortIteration(0, list.size() - 1);
	}
	void quickSortIteration(int left, int right)
	{
		string pivot = list[right];
		string temp;
		int i = left - 1;
		int j = left;
		for (j; j < right; j++)
		{
			if (list[j] <= pivot)
			{
				i++;
				temp = list[i];
				list[i] = list[j];
				list[j] = temp;
			}
		}

		list[right] = list[i + 1];
		list[i + 1] = pivot;
		if (left < i)
		{
			quickSortIteration(left, i);
		}
		if (i + 2<right && i != -1)
		{
			quickSortIteration(i + 2, right);
		}

	}

	/*
	 * mergeSort
	 *
	 * Sorts word list using merge sort
	 */
	void mergeSort()
	{
		int size = list.size() - 1;
		mergeSortIteration(0, size);
	}

	void mergeSortIteration(int low, int high)
	{
		int mid;
		if (low < high)
		{
			mid = (low + high) / 2;
			mergeSortIteration(low, mid);
			mergeSortIteration(mid + 1, high);
			merge(low, mid, high);
		}
	}
	void merge(int low, int mid, int high)
	{
		string tempword;
		vector<string> tempList;
		int l = low, m = mid + 1, h = high;

		while (l <= mid && m <= high)
		{
			if (list[l] < list[m])
			{
				tempList.push_back(list[l]);
				l++;
			}
			else
			{
				tempList.push_back(list[m]);
				m++;
			}
		}

		while (l <= mid)
		{
			tempList.push_back(list[l]);
			l++;
		}
		while (m <= high)
		{
			tempList.push_back(list[m]);
			m++;
		}

		for (int index = low; index <= high; index++)
		{
			list[index] = tempList[index - low];
		}
		list;
	}

	void heapSort()
	{
		heapSortAlgo<string> heap;
		heap.initializeMaxHeap(list);
		heap.heapSort();
		list = heap.getSortedWordList();
		list; // TODO: why is this here
	}
};
