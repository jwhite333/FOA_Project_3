#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "d_except.h"

using namespace std;

enum FIND_QUALIFIER
{
	FOUND = 0,
	SUBSTRING,
	NOT_FOUND

};

struct findResult
{
	int index;
	FIND_QUALIFIER qualifier;

	findResult(int index, FIND_QUALIFIER qualifier) : index(index), qualifier (qualifier) {};
};

enum SORTING_ALGORITHM
{
	INSERTION_SORT = 0,
	QUICK_SORT,
	MERGE_SORT
};

class wordList
{
private:
	// Member variables
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
				std::cin >> input;

				// Catch bad input
				if (std::cin.fail())
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
					std::cout << "ERROR, input not a number" << std::endl;
				if (e == inputError::OUT_OF_RANGE)
					std::cout << "ERROR, input is not one of the available options" << std::endl;

				// Clear cin buffer
				std::cin.clear();
				std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
			}

		} while (error != inputError::NONE);

		// Choose list file
		return availableListFiles[input - 1];
	}

public:

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
				throw fileError("std::getline failed");

			list.push_back(word);
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
				return findResult(guess, FOUND);

			// Change the size of the sublist based on where the guess was in relation to the word
			if (list[guess].compare(word) < 0)
				sublistBegin = guess;
			else
				subListEnd = guess;
		}

		// Word was not found, check if it is a substring
		for (int i = 0; i < (int) word.length(); i++)
		{
			if (word[i] != list[guess][i])
				return findResult(guess, NOT_FOUND);
		}

		// Result is a sibstring of at least one word in the list
		return findResult(guess, SUBSTRING);

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
		}
	}

	/*
	 * insertionSort
	 *
	 * Sorts word list using insertion sort
	 */
	void insertionSort()
	{
		return;
	}

	/*
	 * quickSort
	 *
	 * Sorts word list using quick sort
	 */
	void quickSort()
	{
		return;
	}

	/*
	 * mergeSort
	 *
	 * Sorts word list using merge sort
	 */
	void mergeSort()
	{
		return;
	}
};
