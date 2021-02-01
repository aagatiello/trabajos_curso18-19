#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <array>

using namespace std;

class Sudoku
{
public:

    bool searchRow(array <array<int,9>, 9> tablero, unsigned int row, int value);

    bool searchCol(array <array<int,9>, 9> tablero, unsigned int col, int value);

    bool searchRegion(array <array<int,9>, 9> tablero, unsigned int rows, unsigned int cols, int value);

    bool correctCell(array <array<int,9>, 9> tablero, unsigned int row, unsigned int col, int value);

    bool searchFreeLocation(array <array<int,9>, 9> tablero, unsigned int &row, unsigned int &col);

    bool solveSudoku(array <array<int,9>, 9> &tablero);

    void printSudoku(array <array<int,9>, 9> tablero);

};

#endif // SUDOKU_H
