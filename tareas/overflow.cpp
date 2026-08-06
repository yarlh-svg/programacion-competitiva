#include <iostream>
#include <string>

using namespace std;

int main() {

    string linea;
    
    const double LIMITE = 2147483647;

    while (getline(cin, linea)) {

        cout << linea << endl;

        string n1, n2;
        char op;

        // Separar datos
        cin.clear();

        int i = 0;

        // Leer primer numero
        while (linea[i] != ' ') {
            n1 += linea[i];
            i++;
        }

        i++;

        // Leer operador
        op = linea[i];

        i += 2;

        // Leer segundo numero
        while (i < linea.size()) {
            n2 += linea[i];
            i++;
        }

        // Convertir a double
        double a = stod(n1);
        double b = stod(n2);

        // Verificar numeros
        if (a > LIMITE) {
            cout << "first number too big" << endl;
        }

        if (b > LIMITE) {
            cout << "second number too big" << endl;
        }

        // Resultado
        double resultado;

        if (op == '+') {
            resultado = a + b;
        }
        else {
            resultado = a * b;
        }

        // Verificar resultado
        if (resultado > LIMITE) {
            cout << "result too big" << endl;
        }
    }

    return 0;
}