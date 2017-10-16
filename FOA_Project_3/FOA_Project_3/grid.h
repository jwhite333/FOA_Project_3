#pragma once
#include <vector>
#include <fstream>
#include <functional>

#define ASCII_A 65
#define ASCII_Z 90
#define ASCII_a 97
#define ASCII_z 122
#define ASCII_NEW_LINE 10

using namespace std;

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

};
