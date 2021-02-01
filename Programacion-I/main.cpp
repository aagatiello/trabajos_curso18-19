#include <iostream>
#include <vector>
#include <iomanip>      // define diferentes manipuladores - formato presentacion
#define FILA   1        // fila por defecto

using namespace std;

class Matrix{
public:

    Matrix(int r, int c){
        for(int i{0}; i<r*c; i++){
            data.push_back(0);
        }
        rows = r;
        cols = c;
    }
    void setElement(int row, int col, float value){
        int index = cols*(row-1)+(col-1);
        data.at(index) = value;
    }
    float getElement(int row, int col){
        int index = cols*(row-1)+(col-1);
        return data.at(index);
    }
    int getRows(){
        return rows;
    }
    int getCols(){
        return cols;
    }
    // DETERMINANTE MATRIZ
    bool determinante(float &Tvalor){
        float valor{0},fijo, signo;             // valor recoge el determinante de subMatriz
        int f;
        Matrix aux(rows-1,cols-1);

        if (rows !=cols) return false;
        Tvalor=0;
        f=FILA;                                 // debia chequear la fila con mas ceros, pero por el momento cojo la fila 1
        for (int col{1}; col<=cols; col++){     // recorro las columnas de la fila seleccionada
            if ((f+col) % 2 == 0) signo=1;
            else signo =-1;                     // sumando fila y columna conozco el signo
            fijo = signo * getElement(f,col);   // valor en FILA y columna (con signo segun la posicion)
            subMatriz(f,col,aux);               // subMatriz resultante de quitar la fila 1 y la columna p
            if (aux.rows==1) valor = aux.getElement(1,1);
            else aux.determinante(valor);
            Tvalor+=(fijo*valor);               // voy acumulando los fijo*determinante de la subMatriz
        }
        return true;
    }
    //  MATRIZ INVERSA
    bool inversa(Matrix &aux){
        float valor{0};
        Matrix aux2(rows,cols);
        Matrix aux3(rows,cols);

        if (!determinante(valor) || valor==0) return false;
        adjunta(aux2);                                                      // calcula adjunta y la deja en aux2
        aux2.traspose(aux3);                                                // calcula traspuesta de adjunta y la deja en aux3
        for (int row{1}; row<=rows; row++){
            for (int col{1}; col<=cols; col++){
                aux.setElement(row,col,aux3.getElement(row,col)/valor);     // deja la inversa en aux, divide aux3 por el determinante
            }
        }
        return true;
    }
    // MATRIZ TRASPUESTA
    void traspose(Matrix &aux){
        for (int row{1}; row <= rows; row ++){
            for (int col{1}; col <= cols; col ++){
                aux.setElement(col,row,getElement(row, col));
            }
        }
    }
    // SUMA DE MATRICES
    bool add(Matrix other, Matrix &aux){    // Suma MatrixOne y MatrixTwo y lo devuelve en aux
        if(rows != other.rows || cols != other.cols) return false;
        for (int row{1}; row <= rows; row ++){
            for (int col{1}; col <= cols; col ++){
                aux.setElement( row, col, other.getElement( row, col ) + getElement( row, col ));
            }
        }
        return true;
    }
    // MULTIPLICACION DE MATRICES
    bool multiply(Matrix other,Matrix &aux){  // Multiplica MatrixOne y MatrixTwo y lo devuelve en aux
        float valor;
        if(cols != other.rows) return false;
        for (int rowA{1}; rowA <= rows; rowA++){                    // para cada fila de mi matriz
            for (int colB{1}; colB<=other.cols; colB++) {           // multiplicarla por cada columna de la otra matriz
                valor = 0;
                for (int colA{1}; colA <= cols; colA++){            // para cada columna de la matriz o lo que es lo mismo fila de other
                    int rowB = colA;                                // esto no sirve para nada pero clarifica
                    valor+=getElement(rowA,colA)*other.getElement(rowB,colB);
                }
                aux.setElement(rowA,colB,valor);                    // aux tiene tantas filas como la primera matriz y columnas como la segunda matriz
            }
        }
        return true;
    }

private:
    vector <float> data;
    int rows, cols;

    void subMatriz(int fp, int cp, Matrix &aux){    // fp fila a quitar y cp columna a quitar
        int nf{1}, nc;                              // contadores de numero de fila y columna
        for (int f{1}; f<=rows; f++){
            if (f != fp) {                      	// me salto la fila fp
                nc=1;
                for (int c{1}; c<=cols;c++){
                    if (c != cp){               	// me salto la columna cp
                        aux.setElement(nf,nc,getElement(f,c));
                        nc++;
                    }
                }
                nf++;
            }
        }
    }
    void adjunta(Matrix &aux){
        float valor, signo;
        Matrix aux2(rows-1, cols-1);
        for (int row{1}; row<=rows; row++){
            for (int col{1}; col<=cols; col++){
                subMatriz(row,col,aux2);
                if (aux2.getRows()==1) valor = aux2.getElement(1,1);
                else aux2.determinante(valor);
                if ((row+col) % 2 == 0) signo=1; else signo=-1;
                aux.setElement(row,col,valor*signo);
            }
        }
    }
};

void pideDimension(int &a,int &b){
    cout << "Numero de filas: ";
    cin >> a;
    cout << "Numero de columnas: ";
    cin >> b;
}
void pideDatos(int a, int b, Matrix &Matrix){
    for (int row{1}; row <= a; row ++){
        for (int col{1}; col <= b; col ++){
            cout << "Introduce elemento " << row << ", " << col <<" de la matriz: ";
            float value;
            cin >> value;
            Matrix.setElement(row, col, value);
        }
    }
}
// PINTA AMBAS MATRICES O LA ORIGINAL Y LA TRANSFORMADA
void printMatrix(Matrix matrixOne,Matrix matrixTwo, string texto){
    int rows = (matrixOne.getRows()>matrixTwo.getRows()) ? matrixOne.getRows() : matrixTwo.getRows();
    // ES LO MISMO QUE: if (matrixOne.getRows()>matrixTwo.getRows()) rows=matrixOne.getRows(); else rows=matrixTwo.getRows();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int row{1}; row<=rows; row++){
        for (int col{1}; col<=matrixOne.getCols(); col++){
            cout << fixed << setprecision(2) << right  << setw(10) << setfill(' ');
            if (row<=matrixOne.getRows()) cout << matrixOne.getElement(row,col); else cout << " ";
        }
        if (row==rows/2) cout << texto; else cout << "               ";
        for (int col{1}; col<=matrixTwo.getCols(); col++) {
            cout << fixed << setprecision(2) << right  << setw(10) << setfill(' ');
            if (row<=matrixTwo.getRows()) cout << matrixTwo.getElement(row,col);
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
// PINTA LAS DOS MATRICES Y SU SUMA O PRODUCTO
void print2Matrix(Matrix matrixOne,Matrix matrixTwo, Matrix matrixResult, string texto){
    int rows = (matrixOne.getRows()>matrixTwo.getRows()) ? matrixOne.getRows() : matrixTwo.getRows();
    // ES LO MISMO QUE: if (matrixOne.getRows()>matrixTwo.getRows()) rows=matrixOne.getRows(); else rows=matrixTwo.getRows();
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
    for (int row{1}; row<=rows; row++){
        for (int col{1}; col<=matrixOne.getCols(); col++){
            cout << fixed << setprecision(2) << right  << setw(10) << setfill(' ');
            if (row<=matrixOne.getRows()) cout << matrixOne.getElement(row,col); else cout << " ";
        }
        if (row==rows/2) cout << texto; else cout << "               ";
        for (int col{1}; col<=matrixTwo.getCols(); col++) {
            cout << fixed << setprecision(2) << right  << setw(10) << setfill(' ');
            if (row<=matrixTwo.getRows()) cout << matrixTwo.getElement(row,col); else cout << " ";
        }
        if (row==rows/2) cout << "   Equals ->   "; else cout << "               ";
        for (int col{1}; col<=matrixResult.getCols(); col++) {
            cout << fixed << setprecision(2) << right  << setw(10) << setfill(' ');
            if (row<=matrixResult.getRows()) cout << matrixResult.getElement(row,col);
        }
        cout << endl;
    }
    cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
}
int menu(){
    int option;
    cout << "----------------------------------------" << endl;
    cout << "        ¿Que quieres calcular?          " << endl;
    cout << " 1 DETERMINANTE DE AMBAS MATRICES       " << endl;
    cout << "----------------------------------------" << endl;
    cout << " PRIMERA MATRIZ ---- SEGUNDA MATRIZ     " << endl;
    cout << " 2 INVERSA           4 INVERSA          " << endl;
    cout << " 3 TRASPUESTA        5 TRASPUESTA       " << endl;
    cout << "------------ DOS MATRICES --------------" << endl;
    cout << "            6 SUMAR                     " << endl;
    cout << "            7 MULTIPLICAR               " << endl;
    cout << "----------------------------------------" << endl;
    cout << " 0 TERMINAR EL PROGRAMA                 " << endl;
    cout << "----------------------------------------" << endl;
    cin >> option;
    while (option<0 || option>7){
        cout << "El numero debe ser entre 0 y 7. Elige de nuevo: ";
        cin >> option;
    }
    return option;
}

int main(){
    int option, rows, cols, para;
    float valor;

    cout << "--- BIENVENIDO A MATEMATICAS CON MATRICES ---" << endl;
    cout << "Introduce dos matrices y opera con ellas." << endl << endl;
    cout << "Introduce la PRIMERA matriz:" << endl;
    pideDimension(rows,cols);
    Matrix MatrixOne(rows,cols);
    pideDatos(rows,cols,MatrixOne);
    Matrix aux1(rows,cols);                    // preparada para las ADJUNTA e INVERSA
    Matrix aux2(cols,rows);                    // preparada para la TRASPUESTA -> intercambio filas por columnas
    cout << "Introduce la SEGUNDA matriz:" << endl;
    pideDimension(rows,cols);
    Matrix MatrixTwo(rows,cols);
    pideDatos(rows,cols,MatrixTwo);
    Matrix aux5(rows,cols);                    // preparada para las ADJUNTA e INVERSA
    Matrix aux6(cols,rows);                    // preparada para la TRASPUESTA -> intercambio filas por columnas
    // Pinta las matrices y prepara las matrices auxiliares
    printMatrix(MatrixOne,MatrixTwo," <-1ª     2ª-> ");
    Matrix aux3(rows,cols);                    // Preparada para la SUMA
    Matrix aux4(MatrixOne.getRows(),MatrixTwo.getCols());     // Preparada para la MULTIPLICACION (filas de 1ª y columas de 2ª)

    do {
        option=menu();
        switch (option){
        case 1:
            if (MatrixOne.determinante(valor)) cout << "Determinante primera matriz: " << valor << endl; else cout << "Primera matriz no cuadrada, no se puede calcular. " << endl;
            if (MatrixTwo.determinante(valor)) cout << "Determinante segunda matriz: " << valor << endl; else cout << "Segunda matriz no cuadrada, no se puede calcular. " << endl;
            break;
        case 2:
            if (MatrixOne.inversa(aux1)) printMatrix(MatrixOne, aux1, "   Inversa->   "); else cout << "No tiene inversa." << endl;
            break;
        case 3:
            MatrixOne.traspose(aux2);
            printMatrix(MatrixOne, aux2, "  Traspuesta ->");
            break;
        case 4:
            if (MatrixTwo.inversa(aux5)) printMatrix(MatrixTwo, aux5, "   Inversa->   "); else cout << "No tiene inversa." << endl;
            break;
        case 5:
            MatrixTwo.traspose(aux6);
            printMatrix(MatrixTwo, aux6, "  Traspuesta ->");
            break;
        case 6:
            if (MatrixOne.add(MatrixTwo,aux3)) print2Matrix(MatrixOne, MatrixTwo, aux3, "    Added to ->"); else cout << "No tienen misma dimension, no se puede sumar." << endl;
            break;
        case 7:
            if (MatrixOne.multiply(MatrixTwo,aux4)) print2Matrix(MatrixOne, MatrixTwo, aux4, " Multiply by ->"); else cout << "No coinciden columnas de primera matriz con filas de segunda, no se puede multiplicar." << endl;
            break;
        default: option=0;
            break;
        }
        if (option) {
            cout << "Introduce un numero para volver al menu." << endl;
            cin >> para;
        }
    } while (option);
    cout << "Un placer haberle servido de ayuda. Hasta pronto!" << endl;
}
