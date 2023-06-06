#include "Sudoku.h"
#include <assert.h>
#include <algorithm>

// Grid Data
GridData::GridData(const std::vector<int>& data, int dimension)
	: data(data), dimension(dimension)
{
	// make sure dimension is correct
	assert(dimension == data.size() / dimension);
}

// Sudoku
Sudoku::Sudoku(const GridData& data) 
	: grid(data) 
{
}

// Checks
bool Sudoku::checkRow(int row, int num)
{
	auto res = std::find_if(
		begin() + row * getDimension(),
		begin() + row * getDimension() + getDimension(),
		[&num](const int& elem) { return elem == num; });

	// if res == end num not present
	return res == begin() + row * getDimension() + getDimension();
}
bool Sudoku::checkCol(int col, int num)
{
	// step equal to dimension, so it moves through column
	for (auto it = begin() + col; it != end() - getDimension() + col; it += getDimension())
	{
		if (*it == num) return false;
	}
	return true;
}
bool Sudoku::checkBox(int row, int col, int num)
{
	row -= row % 3;
	col -= col % 3;

	auto boxOriginIt = begin() + row * getDimension() + col;

	// Checks
	for (int i = 0; i < 3; ++i)
	{
		// begin of row and end iterators
		auto begIt = boxOriginIt + getDimension() * i;
		auto endIt = begIt + 3;

		auto res = std::find_if(begIt, endIt, [&num](const int& elem) { return elem == num; });
		
		// num already in box
		if (res != endIt) return false;
	}

	return true;
}
bool Sudoku::canPlace(iterator_type it, int num)
{
	// make sure we use digits
	assert(num > 0 && num < 10);

	// calculate index with iterator distance
	auto index = std::distance(begin(), it);

	// calculate row and index
	int row = (int)index / getDimension();
	int col = index % getDimension();

	// checks all positions
	return checkRow(row, num)
		&& checkCol(col, num)
		&& checkBox(row, col, num);
}

// Friend helpers

/** Place number if possible, then place in next. 
 *  When not possible, return and try another number.
 */
bool solveSudoku(Sudoku& s)
{
	// look for first 0 number
	auto it = std::find_if(s.begin(), s.end(), [](const int& elem) { return elem == 0; });
	if (it == s.end()) return true; // no numbers left, sudoku solved.

	// in sudoku 1-9 used
	for (int num = 1; num <= 9; ++num)
	{
		if (s.canPlace(it, num))
		{
			// place digit
			*it = num;

			// recursive call for next,
			// basically tries to solve sudoku with number that we added
			if (solveSudoku(s)) return true;
			
			// if digit can't be placed we turn back and remove it
			*it = 0;
		}
	}

	// if recursively true not returned - no solution 
	return false;
}

std::ostream& operator<<(std::ostream& os, Sudoku s)
{
	// just simple output
	for (int i = 0; i < s.getDimension(); ++i)
	{
		auto it = s.begin() + (s.getDimension() * i);
		std::copy(it, it + s.getDimension(), std::ostream_iterator<int>(os, ", "));
		os << std::endl;
	}
	return os;
}
