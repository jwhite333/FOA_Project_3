#pragma once
#include <vector>
#include <string>

using namespace std;

enum FIND_QUALIFIER
{
	FOUND = 0,
	SUBSTRING,
	NOT_FOUND

};

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

enum SORTING_ALGORITHM
{
	INSERTION_SORT = 0,
	QUICK_SORT,
	MERGE_SORT,
	HASH_TABLE
};

struct findResult
{
	vector<int> index;
	FIND_QUALIFIER qualifier;

	findResult(vector<int> index, FIND_QUALIFIER qualifier) : index(index), qualifier(qualifier) {};
};

/*
 * MOD
 *
 * Redefines the % operation to return only positive values
 *
 * @param parameter
 * @param base
 */
template <typename T>
inline T MOD(T parameter, T base)
{
	T result = parameter % base;
	if (result < 0)
		return result + base;
	else
		return result;
}