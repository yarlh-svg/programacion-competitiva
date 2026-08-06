#include <iostream>

#define MAX 9

using namespace std;

// Verifica si es válido colocar un número en una posición dada
bool EsValido(int tablero[MAX][MAX], int fila, int col, int num) {
    // Verificar la fila
    for (int j = 0; j < MAX; j++) {
        if (tablero[fila][j] == num)
            return false;
    }

    // Verificar la columna
    for (int i = 0; i < MAX; i++) {
        if (tablero[i][col] == num)
            return false;
    }

    // Verificar el bloque 3x3
    int filaInicio = (fila / 3) * 3;
    int colInicio  = (col  / 3) * 3;
    for (int i = filaInicio; i < filaInicio + 3; i++) {
        for (int j = colInicio; j < colInicio + 3; j++) {
            if (tablero[i][j] == num)
                return false;
        }
    }

    return true;
}

// backtracking
bool SolucionarSudoku(int tablero[MAX][MAX]) {
    for (int fila = 0; fila < MAX; fila++) {
        for (int col = 0; col < MAX; col++) {
            // Buscar una celda vacía (valor 0)
            if (tablero[fila][col] == 0) {
                // Intentar colocar los números del 1 al 9
                for (int num = 1; num <= 9; num++) {
                    if (EsValido(tablero, fila, col, num)) {
                        tablero[fila][col] = num;

                        // Llamada recursiva
                        if (SolucionarSudoku(tablero))
                            return true;

                        // Backtrack: deshacer la asignación
                        tablero[fila][col] = 0;
                    }
                }
                // No se encontró ningún número válido: retroceder
                return false;
            }
        }
    }
    // Todas las celdas están llenas: solución encontrada
    return true;
}

void Imprimir(int tablero[MAX][MAX]) {
    for (int fila = 0; fila < MAX; fila++) {
        if (fila % 3 == 0 && fila != 0) {
            cout << "------+-------+------" << endl;
        }

        for (int col = 0; col < MAX; col++) {
            if (col % 3 == 0 && col != 0) {
                cout << "| ";
            }

            cout << tablero[fila][col] << " ";
        }

        cout << endl;
    }
}

int main() {
    freopen("in.txt", "r", stdin);

    // Ingresamos los valores del sudoku
    // Finaliza cuando termine de leer la entrada
    int tablero[MAX][MAX] = {};
    int pos_x, pos_y, valor;

    while (cin >> pos_x >> pos_y >> valor)
        tablero[pos_x - 1][pos_y - 1] = valor;

    cout << "Tablero inicial:" << endl;
    Imprimir(tablero);

    cout << endl;

    if (SolucionarSudoku(tablero)) {
        cout << "Solucion:" << endl;
        Imprimir(tablero);
    } else {
        cout << "No tiene solucion." << endl;
    }

    return 0;
}