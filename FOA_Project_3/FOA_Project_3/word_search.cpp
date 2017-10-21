/*
* Name: Jun Jie Chen, Jon White
* Project 3
* Group: 5
* Platform: Microsoft Visual Studio
*/

#include <ctime>
#include "word_list.h"
#include "grid.h"
#include "hash.h"

/*
 * findMatches
 *
 * Prints out all words from the word list that can be found in the grid
 */
void findMatches(wordList * wordList, grid * letterMatrix, SORTING_ALGORITHM algorithm)
{
	// Search through the word search looking for words
	letterMatrix->findWords(wordList, algorithm);
}

/*
 * search
 *
 * Reads the name of the grid file from the keyboard and prints out all words from the word list that can be found in the grid.The function should also
 * print out the CPU time to sort the words, the CPU time to find the words, and the total time.
 * The integer parameter is used to select the sorting algorithm used
 */
void search(SORTING_ALGORITHM algorithm, wordList * wordList, grid * letterMatrix)
{
	// Start program timer
	clock_t startProgram = clock();

	// Read in letter matrix
	try
	{
		letterMatrix->readCharMatrix();
	}
	catch (baseException e)
	{
		cout << e.what();
	}

	// Begin algorithm timer
	clock_t algorithmBegin = clock();
	switch (algorithm)
	{
		case HASH_TABLE:
		{
			// Read in word list and store in hash table
			
			hashTable hashTable(9007); // constructor with optional int arguement for non null
			try
			{
				wordList->readlist();
			}
			catch (baseException e)
			{
				cout << e.what();
			}
		}
		break;

		case INSERTION_SORT:
		case QUICK_SORT:
		case MERGE_SORT:
		case HEAP_SORT:
		{
			// Read in word list and store in string vector
			try
			{
				wordList->readlist();
			}
			catch (baseException e)
			{
				cout << e.what();
			}

			// Run sorting algorithm
			wordList->sort(algorithm);
		}
		break;
	}

	// Get algorithm run time
	double algorithmRunTime = (clock() - algorithmBegin) / (double)CLOCKS_PER_SEC;

	// Find matches
	clock_t findMatchBegin = clock();
	findMatches(wordList, letterMatrix, algorithm);
	
	// Get find match time and total run time
	double findMatchDuration = (clock() - findMatchBegin) / (double)CLOCKS_PER_SEC;
	double totalDuration = (clock() - startProgram) / (double)CLOCKS_PER_SEC;
	
	// Print results
	cout << "Results: " << endl
		<< "Algorithm runtime (s): " << algorithmRunTime << endl
		<< "Find Word runtime (s): " << findMatchDuration << endl
		<< "Total time (s): " << totalDuration << endl;
}

/*
 * main
 *
 * Program entry point
 */
int main()
{
	wordList wordList(HEAP_SORT);
	grid letterMatrix;

	search(HEAP_SORT, &wordList, &letterMatrix);
	
	system("pause");
	return 0;
}