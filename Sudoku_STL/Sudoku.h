#pragma once
#include <iostream>
#include <vector>

/** Simple struct to store sudoku field and size
*/
struct GridData
{
	GridData(const std::vector<int>& data, int dimension);

	std::vector<int> data;
	int dimension;
};

/** Simple Sudoku class, that stores field,
 *  can checks rules and solve it.
 *  Iterators used for training, indexes and 2d array will look easier.
*/
class Sudoku {
	using iterator_type = std::vector<int>::iterator;
public:
	friend std::ostream& operator<<(std::ostream& os, Sudoku sudoku);
	friend bool solveSudoku(Sudoku& s);

	explicit Sudoku(const GridData& data);

private:
	/* Shortcuts for getting values from field data. */
	int getDimension() const { return grid.dimension; }
	iterator_type begin() { return grid.data.begin(); }
	iterator_type end() { return grid.data.end(); }

	/* Checks */
	bool checkRow(int row, int num);
	bool checkCol(int col, int num);
	bool checkBox(int row, int col, int num);

	/* Number can be placed only if all checks passed. */
	bool canPlace(iterator_type it, int num);

	GridData grid;
};
