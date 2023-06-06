#include <iostream>
#include "Sudoku.h"

/** Backtracking Sudoku solver,
*	works with 3x3 6x6 9x9 etc
*	O(9^n*n) 
*/ 

int main(void)
{
	// Game field
	int dimension = 9;
	std::vector<int> field{ 0,0,2, 7,0,1, 9,0,0,
							 0,6,0, 0,0,2, 3,8,0,
							 9,5,0, 0,6,0, 0,0,1,

							 2,7,0, 0,4,0, 0,0,9,
							 0,0,4, 6,0,3, 8,0,0,
						     3,0,0, 0,7,0, 0,1,5,

							 8,0,0, 0,1,0, 0,6,2,
						     0,3,9, 5,0,0, 0,4,0,
						     0,0,1, 4,0,7, 5,0,0 };

	// Wraps field data
	GridData data(field,dimension);

	// Sudoku object based on field
	Sudoku sudoku(data);

	// Sudoku before solving
	std::cout << sudoku << std::endl;
	
	// Sudoku solving
	if (solveSudoku(sudoku))
	{
		std::cout << sudoku << std::endl;
	}
	else {
		std::cout << "no solution found" << std::endl;
	}

	return 0;
}
