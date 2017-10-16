#pragma once
#include <vector>
#include <fstream>
#include <thread>
#include "word_list.h"

// Input parameters
#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_a 97
#define ASCII_z 122
#define ASCII_NEW_LINE 10

// Matrix parameters
#define MATRIX_DIRECTIONS 8
#define MIN_WORD_LENGTH 5

using namespace std;

enum SEARCH_DIRECTION
{
	NORTH = 0,
	NORTH_EAST,
	EAST,
	SOUTH_EAST,
	SOUTH,
	SOUTH_WEST,
	WEST,
	NORTH_WEST,
	DIRECTION_NUM
};

class grid
{
private:
	// Member variables
	vector<vector<char>> letterMatrix;
	vector<string> availableMatrixFiles = { "input15.txt", "input30.txt", "input50.txt", "input250.txt" };

	/*
	 * pickMatrixFile
	 *
	 * Chooses one of the list files to open
	 */
	string pickMatrixFile()
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
				for (int i = 0; i < (int)availableMatrixFiles.size(); i++)
				{
					cout << i + 1 << " - " << availableMatrixFiles[i] << endl;
				}
				cout << "Enter numerical choice: ";
				std::cin >> input;

				// Catch bad input
				if (std::cin.fail())
					throw inputError::NOT_A_NUM;

				// Catch out of range input
				if (input <= 0 || input > (int)availableMatrixFiles.size())
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
		return availableMatrixFiles[input - 1];
	}

public:

	/*
	 * readCharMatrix
	 *
	 * Reads letters from the specified text file and returns them in a matrix
	 */
	void readCharMatrix()
	{
		// Open file
		string file = pickMatrixFile();
		ifstream inFile;
		inFile.open(file.c_str(), ios::binary);
		inFile.unsetf(ios_base::skipws); // Don't skip whitespace
		if (inFile.bad())
			throw fileOpenError(file);

		// Initialize vector, overwriting old vector if necessary
		if ((int)letterMatrix.size() > 0)
			letterMatrix.clear();
		
		// Read file
		char letter;
		int currentRow = -1; // A newline after the matrix size will incriment this to 0 when real values start
		while (inFile >> letter)
		{
			if (inFile.bad())
				throw fileError("std::getline failed");

			// Check for uppercase letters
			if ((int) letter >= ASCII_A && (int) letter <= ASCII_Z)
				letterMatrix[currentRow].push_back(letter);

			// Check for lowercase letters
			if ((int)letter >= ASCII_a && (int)letter <= ASCII_z)
				letterMatrix[currentRow].push_back(letter);

			// Check for end of line chars
			if ((int)letter == ASCII_NEW_LINE)
			{
				letterMatrix.resize(letterMatrix.size() + 1);
				currentRow++;
			}
		}
	}

	/*
	 * print
	 *
	 * Prints the char matrix to sdout
	 */
	void print()
	{
		cout << "Grid contains:" << endl << endl;
		for (int row = 0; row < (int)letterMatrix.size(); row++)
		{
			for (int column = 0; column < (int)letterMatrix[row].size(); column++)
			{
				cout << " " << letterMatrix[row][column];
			}
			cout << endl;
		}
	}

	/*
	 * getWord
	 *
	 * Gets word from specified direction from matrix
	 */
	string getWord(int row, int column, int direction, int wordSize)
	{
		// Create a word of designated size
		string word = "";

		// Get matrix dimentions
		int length = letterMatrix[0].size();
		int height = letterMatrix.size();
		
		switch (direction)
		{
		case NORTH:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row - i) % height;
				word += letterMatrix[rowIndex][column];
			}
			break;
		case NORTH_EAST:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row - i) % height;
				int columnIndex = (column + i) % length;
				word += letterMatrix[rowIndex][columnIndex];
			}
			break;
		case EAST:
			for (int i = 0; i < wordSize; i++)
			{
				int columnIndex = (column + i) % length;
				word += letterMatrix[row][columnIndex];
			}
			break;
		case SOUTH_EAST:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row + i) % height;
				int columnIndex = (column + i) % length;
				word += letterMatrix[rowIndex][columnIndex];
			}
			break;
		case SOUTH:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row + i) % height;
				word += letterMatrix[rowIndex][column];
			}
			break;
		case SOUTH_WEST:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row + i) % height;
				int columnIndex = (column - i) % length;
				word += letterMatrix[rowIndex][columnIndex];
			}
			break;
		case WEST:
			for (int i = 0; i < wordSize; i++)
			{
				int columnIndex = (column - i) % length;
				word += letterMatrix[row][columnIndex];
			}
			break;
		case NORTH_WEST:
			for (int i = 0; i < wordSize; i++)
			{
				int rowIndex = (row + i) % height;
				int columnIndex = (column - i) % length;
				word += letterMatrix[rowIndex][columnIndex];
			}
			break;
		}

		// Return new word
		return word;
	}

	/*
	 * findWords
	 *
	 * Finds words contained in the matrix using the specified wordlist
	 */
	void findWords(wordList * wordList)
	{
		// Kick off threads to each seach the matrix for a specific direction
		thread threads[(int)DIRECTION_NUM];
		for (int direction = 0; direction < (int)DIRECTION_NUM; direction++)
		{
			threads[direction] = thread (&grid::directionalWordFind, this, wordList, direction);
		}

		// CLose out all threads when they are done
		for (int direction = 0; direction < (int)DIRECTION_NUM; direction++)
		{
			threads[direction].join();
		}
	}

	/*
	 * directionalWordFind
	 *
	 * Looks through the matrix and checks one specific direction of words each time it moves to a new letter
	 */
	void directionalWordFind(wordList * wordList, int direction)
	{
		// Traverse the matrix
		for (int row = 0; row < (int)letterMatrix.size(); row++)
		{
			for (int column = 0; column < (int)letterMatrix[row].size(); column++)
			{
				for (int wordSize = MIN_WORD_LENGTH; wordSize < (int) letterMatrix[row].size(); wordSize++)
				{
					// Get word from matrix
					string word = getWord(row, column, direction, wordSize);

					// Look for word in the list
					findResult result = wordList->find(word);

					// If word is found, print it
					if (result.qualifier == FOUND)
						wordList->print(result.index);

					// If word fragment is potentially part of a larger word, keep incrimenting the size
					else if (result.qualifier == SUBSTRING)
						continue;

					// If the word was not found at all, this direction will not yeild any more words
					else
						break;
				}
			}
		}
	}

	 void test(int number)
	 {
		 cout << "Hello from number: " << number << endl;
	 }

};
