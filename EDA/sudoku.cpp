#include "sudoku.h"

// BUSCA SI HAY UN MISMO NUMERO EN UNA FILA
bool Sudoku::searchRow(array <array<int,9>, 9> tablero, unsigned int row, int value)
{
    for(unsigned int col = 0; col < 9; col++){
        if(tablero.at(row).at(col) == value) return true;
    }
    return false;
}

// BUSCA SI HAY UN MISMO NUMERO EN UNA COLUMNA
bool Sudoku::searchCol(array <array<int,9>, 9> tablero, unsigned int col, int value)
{
    for(unsigned int row = 0; row < 9; row++){
        if(tablero.at(row).at(col) == value) return true;
    }
    return false;
}

// BUSCA QUE NO SE REPITA UN MISMO NUMERO EN UNA REGION (CUADRADO 3x3)
bool Sudoku::searchRegion(array <array<int,9>, 9> tablero, unsigned int rows, unsigned int cols, int value)
{
    for(unsigned int row = 0; row < 3; row++){
        for(unsigned int col = 0; col < 3; col++){
            if(tablero.at(row+rows).at(col+cols) == value) return true;
        }
    }
    return false;
}

// ASEGURA QUE LA POSICION ES CORRECTA SI NO SE CUMPLE NINGUNA DE LAS FUNCIONES ANTERIORES
bool Sudoku::correctCell(array <array<int,9>, 9> tablero, unsigned int row, unsigned int col, int value)
{
    return !searchRow(tablero, row, value) &! searchCol(tablero, col, value) &! searchRegion(tablero, row-row%3, col-col%3, value);
}

// BUSCA LAS CELDAS LIBRES
bool Sudoku::searchFreeLocation(array <array<int,9>, 9> tablero, unsigned int &row, unsigned int &col)
{
    for(row = 0; row < 9; row++){
        for(col = 0; col < 9; col++){
            if(tablero.at(row).at(col) == 0) return true;
        }
    }
    return false;
}

// RELLENA LAS CELDAS LIBRES
bool Sudoku::solveSudoku(array <array<int,9>, 9> &tablero)      // Algoritmo de Backtracking
{
    unsigned int row, col;

    if(!searchFreeLocation(tablero, row, col)) return true;     // Si está completo, termina

    for(int value = 1; value < 10; value++){                    // Entre numeros del 1 al 9
        if(correctCell(tablero, row, col, value)){              // Comprueba que cumple los requisitos para colocar un numero en una celda
            tablero.at(row).at(col) = value;
            if(solveSudoku(tablero)) return true;
            tablero.at(row).at(col) = 0;                        // Si no es posible rellenar de forma valida, se iguala a 0 y vuelve atrás
        }
    }
    return false;                                               // Si ha probado todos los numeros y ninguno es correcto, vuelve a una posicion anterior a probar con otro numero
}

// IMPRIME EL SUDOKU
void Sudoku::printSudoku(array <array<int,9>, 9> tablero)
{
    for(unsigned int row = 0; row < 9; row++){
        if(row % 3 == 0){
            cout << "-----------------------" << endl;
        }
        for(unsigned int col = 0; col < 9; col++){
            cout << " " << tablero.at(row).at(col);
            if(col == 2 || col == 5){
                cout  << " |";
            }
        }
        cout << endl;
    }
    cout << "-----------------------" << endl;
}
