#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "d_except.h"

using namespace std;

class wordList
{
private:
	// Member variables
	vector<string> * list;
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
		return availableListFiles[input];
	}

public:
	/*
	* constructor
	*
	* Initializes word list to be NULL
	*/
	wordList()
	{
		list = NULL;
	}

	/*
	 * destructor
	 *
	 * Cleans up the word list if it exists
	 */
	~wordList()
	{
		if (list)
			delete list;
	}

	/*
	 * readlist
	 *
	 * Reads words from the specified text file and returns them in a vector of strings
	 *
	 * @param file
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
		if (list)
			delete list;
		list = new vector<string>;

		// Read file
		string word;
		while (getline(inFile, word))
		{
			if (inFile.bad())
				throw fileError("std::getline failed");

			list->push_back(word);
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

		// Check if word list exists yet
		if (!list)
		{
			cout << "Nothing" << endl;
			return;
		}

		// Otherwise print words
		for (int i = 0; i < (int)list->size(); i++)
		{
			cout << (*list)[i] << endl;
		}
	}
};
