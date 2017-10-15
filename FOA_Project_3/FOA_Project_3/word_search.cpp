#include "word_list.h"

int main()
{
	wordList wordList;

	try
	{
		wordList.readlist();
	}
	catch (baseException e)
	{
		cout << e.what();
	}
	
	wordList.print();

	system("pause");
	return 0;
}