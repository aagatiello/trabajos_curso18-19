#include <iostream>
#include <array>
#include <fstream>
#include <sstream>

#include "sudoku.h"

using namespace std;

int main(){

    cout << "--------------------   RESOLVER SUDOKU AUTOMATICAMENTE   --------------------" << endl << endl;

    Sudoku sudoku;
    array <array<int,9>, 9> tablero;

    cout << "Escribe la ruta y nombre del fichero: ";
    string name;
    getline(cin,name);

    ifstream ficheroEntrada;    // Crea el fichero
    int row = 0, col = 0;

    ficheroEntrada.open(name.c_str(), ios::in);
    if(ficheroEntrada.is_open()){
        string line;

        while(getline(ficheroEntrada,line)){
            istringstream value(line);      // Comando que te permite operar con strings
            string result;

            while (getline(value,result,',')){
                tablero.at(row).at(col) = atoi(result.c_str());     // Convierte el string a int
                col = col+1;
            }
            row = row+1;
            col = 0;
        }

        cout << endl << "Sudoku a resolver:" << endl;
        sudoku.printSudoku(tablero);

        if(sudoku.solveSudoku(tablero) == true){
            cout << endl << "Solucion:" << endl;
            sudoku.printSudoku(tablero);
            cout << endl;
        }else{
            cout << endl << "Este sudoku no tiene solucion." << endl;
        }

        ficheroEntrada.close();
    }
    else cout << endl << "El archivo '" << name << "' no existe." << endl;

    return 0;
}
