#include <ctime>
#include "word_list.h"
#include "grid.h"

/*
 * findMatches
 *
 * Prints out all words from the word list that can be found in the grid
 */
void findMatches(wordList * wordList, grid * letterMatrix)
{
	// Search through the word search looking for words
	letterMatrix->findWords(wordList);
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
	// Read in letter matrix
	try
	{
		letterMatrix->readCharMatrix();
	}
	catch (baseException e)
	{
		cout << e.what();
	}

	// Read in word list
	try
	{
		wordList->readlist();
	}
	catch (baseException e)
	{
		cout << e.what();
	}

	// Start timer
	std::clock_t start = std::clock();

	// Run sorting algorithm
	wordList->sort(algorithm);
	
	// Print out run time
	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Sorting time (s): " << duration << endl;
	
	
	//start timer for find match
	std::clock_t start2 = std::clock();
	// Find matches
	
	//findMatches(wordList, letterMatrix);					//Commented out so it doesn't attempt to search in an unsorted list
	
	//Print out run time
	double duration2 = (std::clock() - start2) / (double)CLOCKS_PER_SEC;
	std::cout << "Find match time (s): " << duration2 << endl;
	
	//Print out total time
	double totalTime = duration + duration2;
	std::cout << "Total time (s): " << totalTime << endl;

}

/*
 * main
 *
 * Program entry point
 */
int main()
{
	wordList wordList;
	grid letterMatrix;

	search(MERGE_SORT, &wordList, &letterMatrix);
	
	system("pause");
	return 0;
}