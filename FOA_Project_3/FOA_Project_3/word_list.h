#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "d_except.h"

using namespace std;

class wordList
{
	wordList();

	/*
	 * readWordList
	 *
	 * Reads words from the specified text file and returns them in a vector of strings
	 *
	 * @param file
	 */
	vector<string> * readWordList(string file)
	{
		// Open file
		ifstream inFile;
		inFile.open(file.c_str());
		if (inFile.bad)
			throw fileOpenError(file);

		// Initialize vector
		vector<string> * wordList = new vector<string>;

		// Read file
		string word;
		while (getline(inFile, word))
		{
			if (inFile.bad)
				throw fileError("std::getline failed");

			wordList->push_back(word);
		}

		return wordList;
	}
};
