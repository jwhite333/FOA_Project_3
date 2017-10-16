#include "word_list.h"
#include "grid.h"

int main()
{
	wordList wordList;
	grid grid;

	/*try
	{
		wordList.readlist();
	}
	catch (baseException e)
	{
		cout << e.what();
	}*/

	try
	{
		grid.readCharMatrix();
	}
	catch (baseException e)
	{
		cout << e.what();
	}
	grid.print();

	system("pause");
	return 0;
}