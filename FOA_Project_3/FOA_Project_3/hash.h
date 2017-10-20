#pragma once
#include <string>
#include <vector>
#include "helpers.h"

using namespace std;

class hashTable
{
private:
	int n;
	vector<vector<string>> table;

	/*
	 * hash
	 *
	 * Returns an index indicating where to store the value
	 *
	 * @param value
	 */
	int hash(string word)
	{
		long long sum = 0;
		for (int index = 0; index < (int)word.length(); index++)
		{
			sum += (long long) word[index] * (long long) pow(128.0, (float)index);
		}

		return (int) MOD(sum, (long long) n);
	}


public:
	/*
	 * constructor
	 *
	 * Initializes hash table of the given size
	 *
	 * @param n
	 */
	hashTable(int size)
	{
		n = size;
		table.resize(size);
	}

	/*
	 * inList
	 *
	 * Searches for an item in the hash table
	 * If the word is not in the list, return substring if it is a substring of a word in the list
	 *
	 * @param word
	 */
	findResult inList(string word)
	{
		// Hash value
		int index = hash(word);

		// Look through "bin" for word
		for (int element = 0; element < (int)table[index].size(); element++)
		{
			// Found the word
			if (table[index][element] == word)
				return findResult({ index, element }, FOUND);
		}

		// Did not find word
		return findResult({}, NOT_FOUND);
	}

	/*
	 * addItem
	 *
	 * Adds a string to the hash table
	 *
	 * @param word
	 */
	void addItem(string word)
	{
		// Hash value
		int index = hash(word);

		// Add the word to the table
		table[index].push_back(word);
	}

	/*
	 * removeItem
	 *
	 * Removes a string from the hash table if it exists
	 *
	 * @param word
	 */
	void removeItem(string word)
	{
		// Check if string exists in list
		findResult find = inList(word);

		// Word exists
		if (find.qualifier == FOUND)
		{
			// Use vector.erase to remove word
			auto iterator = table[find.index[0]].begin() + find.index[1];
			table[find.index[0]].erase(iterator);
		}
	}

	/*
	 * print
	 *
	 * Print an item from the hash table
	 *
	 * @param word
	 */
	void print(int index1, int index2)
	{
		// Print
		if ((index1 >= 0 && index1 < (int)table.size()) && (index2 >= 0 && index2 < (int)table[0].size()))
			cout << table[index1][index2] << endl;
		
	}
};